// based on ofxThreadedImageLoader

#include "TXThreadedImageLoader.h"
#include <sstream>
TXThreadedImageLoader::TXThreadedImageLoader() 
:ofThread()
{
	nextID = 0;
    ofAddListener(ofEvents().update, this, &TXThreadedImageLoader::update);
	ofAddListener(ofURLResponseEvent(),this,&TXThreadedImageLoader::urlResponse);
    
    startThread();
    lastUpdate = 0;
}

TXThreadedImageLoader::~TXThreadedImageLoader(){
	condition.signal();
    ofRemoveListener(ofEvents().update, this, &TXThreadedImageLoader::update);
	ofRemoveListener(ofURLResponseEvent(),this,&TXThreadedImageLoader::urlResponse);
}

// Load an image from disk.
//--------------------------------------------------------------
void TXThreadedImageLoader::loadFromDisk(ofImage& image, string filename) {
	nextID++;
	ofImageLoaderEntry entry(image, OF_LOAD_FROM_DISK);
	entry.filename = filename;
	entry.id = nextID;
	entry.image->setUseTexture(false);
	entry.name = filename;
    
    lock();
    images_to_load_buffer.push_back(entry);
    condition.signal();
    unlock();
}


// Load an url asynchronously from an url.
//--------------------------------------------------------------
void TXThreadedImageLoader::loadFromURL(ofImage& image, string url) {
	nextID++;
	ofImageLoaderEntry entry(image, OF_LOAD_FROM_URL);
	entry.url = url;
	entry.id = nextID;
	entry.image->setUseTexture(false);	
	entry.name = "image" + ofToString(entry.id);

    lock();
	images_to_load_buffer.push_back(entry);
    condition.signal();
    unlock();
}


// Reads from the queue and loads new images.
//--------------------------------------------------------------
void TXThreadedImageLoader::threadedFunction() {
    deque<ofImageLoaderEntry> images_to_load;

	while( isThreadRunning() ) {
		lock();
		if(images_to_load_buffer.size() ){
            images_to_load.insert( images_to_load.end(),
                                images_to_load_buffer.begin(),
                                images_to_load_buffer.end() );

            images_to_load_buffer.clear();
        }
		unlock();
        
        
        while( !images_to_load.empty() ) {
            
            // testing xxx
            ofImageLoaderEntry  & entry = images_to_load.front();
            //ofImageLoaderEntry  & entry = images_to_load.back();  // testing xxx
            
            if(entry.type == OF_LOAD_FROM_DISK) {
                if(! entry.image->load(entry.filename) )  { 
                    ofLogError("TXThreadedImageLoader") << "couldn't load file: \"" << entry.filename << "\"";
                }
                
                lock();
                images_to_update.push_back(entry);
                unlock();
            }else if(entry.type == OF_LOAD_FROM_URL) {
                lock();
                images_async_loading.push_back(entry);
                unlock();
                
                ofLoadURLAsync(entry.url, entry.name);
            }

            // testing xxx
            images_to_load.pop_front();
            //images_to_load.clear();// testing xxx
        }
	}
}


// When we receive an url response this method is called; 
// The loaded image is removed from the async_queue and added to the
// update queue. The update queue is used to update the texture.
//--------------------------------------------------------------
void TXThreadedImageLoader::urlResponse(ofHttpResponse & response) {
	if(response.status == 200) {
		lock();
		
		// Get the loaded url from the async queue and move it into the update queue.
		entry_iterator it = getEntryFromAsyncQueue(response.request.name);
		if(it != images_async_loading.end()) {
			(*it).image->load(response.data);
			images_to_update.push_back(*it);
			images_async_loading.erase(it);
		}
		
		unlock();
	}else{
		// log error.
		ofLogError("TXThreadedImageLoader") << "couldn't load url, response status: " << response.status;
		ofRemoveURLRequest(response.request.getID());
		// remove the entry from the queue
		lock();
		entry_iterator it = getEntryFromAsyncQueue(response.request.name);
		if(it != images_async_loading.end()) {
			images_async_loading.erase(it);
		}
		unlock();
	}
}


// Check the update queue and update the texture
//--------------------------------------------------------------
void TXThreadedImageLoader::update(ofEventArgs & a){
    
    // Load 1 image per update so we don't block the gl thread for too long
    
    lock();
	if (!images_to_update.empty()) {

		ofImageLoaderEntry entry = images_to_update.front();

		const ofPixels& pix = entry.image->getPixels();
		entry.image->getTexture().allocate(
				 pix.getWidth()
				,pix.getHeight()
				,ofGetGlInternalFormat(pix)
		);
		
		entry.image->setUseTexture(true);
		entry.image->update();

		images_to_update.pop_front();
	}
    unlock();
}


// Find an entry in the aysnc queue.
//   * private, no lock protection, is private function
//--------------------------------------------------------------
TXThreadedImageLoader::entry_iterator TXThreadedImageLoader::getEntryFromAsyncQueue(string name) {
	entry_iterator it = images_async_loading.begin();
	for(;it != images_async_loading.end();it++) {
		if((*it).name == name) {
			return it;
		}
	}
	return images_async_loading.end();
}


// ================================= added by paul:

bool TXThreadedImageLoader::hasFinishedLoading() {
    bool finished;
    lock();
    finished = images_to_update.empty();
    unlock();
    return finished;
}

void TXThreadedImageLoader::clearAll() {
    lock();
    
    images_async_loading.clear();
    images_to_load_buffer.clear();
    images_to_update.clear();
    
    unlock();
}

