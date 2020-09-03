/*
 *  Copyright 2013 Paul Miller. All rights reserved.
 *
 */

#include "TXModuleBase.h"
#include "TXSystem.h"

// properties

// constructor
TXModuleBase::TXModuleBase () :
    parentSystem(NULL),
    moduleID(0),
    moduleType(""),
    name(""),
    freezeModule(false),
    canDraw(false),
    canDrawLayers(false),
    hasTexture(false),
    masterBpm(120)
    {}

// methods

void TXModuleBase::baseSetup (TXSystem * parentSystemArg, int moduleIDArg, string moduleTypeArg, string moduleNameArg) {
    setParentSystem(parentSystemArg);
    moduleID = moduleIDArg;
    moduleType = moduleTypeArg;
    name = moduleNameArg;
    parameters.setName(name);
}

void TXModuleBase::setParentSystem(TXSystem * parentSystemArg) {
    parentSystem = parentSystemArg;
}

void TXModuleBase::initialiseParameters() {
    clearParameters();
}

int TXModuleBase::getModuleID() {
    return moduleID;
}

void TXModuleBase::setModuleID(int moduleIDArg) {
    moduleID = moduleIDArg;
}

string TXModuleBase::getName() {
    return name;
}

void TXModuleBase::setName(string nameArg) {
    name = nameArg;
}

string TXModuleBase::getModuleType() {
    return moduleType;
}

void TXModuleBase::setModuleType(string moduleTypeArg) {
    moduleType = moduleTypeArg;
}


bool TXModuleBase::getFreezeModule() {
    return freezeModule;
}

void TXModuleBase::setFreezeModule(bool freezeModuleArg) {
    freezeModule = freezeModuleArg;
}

int TXModuleBase::getWindowWidth() {
    int outVal;
    if (parentSystem) {
        outVal = parentSystem->getWindowWidth();
    } else {
        outVal = ofGetWidth();
    }
    return outVal;
}

int TXModuleBase::getWindowHeight() {
    int outVal;
    if (parentSystem) {
        outVal = parentSystem->getWindowHeight();
    } else {
        outVal = ofGetHeight();
    }
    return outVal;
}

// dummy methods - can be overridden in subclasses

void TXModuleBase::update() {};

void TXModuleBase::windowResized(int w, int h) {}

void TXModuleBase::message(string stringArg) {};

void TXModuleBase::draw() {};

void TXModuleBase::addDrawModule(int moduleIDArg, int layerNoArg) {};

void TXModuleBase::removeDrawModule(int moduleIDArg, int layerNoArg) {};

void TXModuleBase::resetTime() {};

void TXModuleBase::advanceBy(float timeDeltaArg){};

void TXModuleBase::setMasterBpm(float masterBpmArg){
    masterBpm = masterBpmArg;
};

void TXModuleBase::processOscMsg(ofxOscMessage msg){};

// override super class
void TXModuleBase::markForDeletion() {
    markedForDeletion = true;
    // mark all mod parameters and mod sources for deletion
    map<string, ofPtr <TXModParameter> >::iterator iter1 = modParameters.begin();
    for (iter1=modParameters.begin(); iter1!=modParameters.end(); ++iter1)
    {
        iter1->second->markForDeletion();
    }
    map<string, ofPtr <TXModSource> >::iterator iter2 = modSources.begin();
    for (iter2=modSources.begin(); iter2!=modSources.end(); ++iter2)
    {
        iter2->second->markForDeletion();
    }
}

////////////////////////////////

ofPtr<TXModSource> TXModuleBase::createModSource(string name, float value) {
    ofPtr<TXModSource> newModSource(new TXModSource);
    newModSource->setup(name, value);
    modSources[name] = newModSource;
    return newModSource;
}

bool TXModuleBase::isValidModSource(string sourceName) {
    map<string, ofPtr <TXModSource> >::iterator iter = modSources.find(sourceName);
    if (iter != modSources.end()) {
        return true;
    } else {
        return false;
    };
};

void TXModuleBase::resetModulation() {
    map<string, ofPtr <TXModParameter> >::iterator iter = modParameters.begin();
    for (iter=modParameters.begin(); iter!=modParameters.end(); ++iter)
    {
        iter->second->resetModulation();
    }
}

////////////////////////////////

ofXml TXModuleBase:: getXMLData() {
    ofXml XML;
    XML.addChild("module");
    XML.setTo("module");
    XML.addValue("moduleID", getModuleID());

    if (extImageModuleSlots.size() > 0) {
        // add assets
        XML.addChild("extImageModuleSlots");
        XML.setTo("extImageModuleSlots");
        for (auto extImageModuleSlot: extImageModuleSlots) {
            ofXml tempXML;
            tempXML.addChild("extImageModuleSlot");
            tempXML.setTo("extImageModuleSlot");
            tempXML.addValue("slotName", extImageModuleSlot.first);
            tempXML.addValue("moduleID", extImageModuleSlot.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (imageAssetSlots.size() > 0) {
        XML.addChild("imageAssetSlots");
        XML.setTo("imageAssetSlots");
        for (auto imageAssetSlot: imageAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("imageAssetSlot");
            tempXML.setTo("imageAssetSlot");
            tempXML.addValue("slotName", imageAssetSlot.first);
            tempXML.addValue("assetID", imageAssetSlot.second.first);
            tempXML.addValue("assetBankNo", imageAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (movieAssetSlots.size() > 0) {
        XML.addChild("movieAssetSlots");
        XML.setTo("movieAssetSlots");
        for (auto movieAssetSlot: movieAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("movieAssetSlot");
            tempXML.setTo("movieAssetSlot");
            tempXML.addValue("slotName", movieAssetSlot.first);
            tempXML.addValue("assetID", movieAssetSlot.second.first);
            tempXML.addValue("assetBankNo", movieAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (svgAssetSlots.size() > 0) {
        XML.addChild("svgAssetSlots");
        XML.setTo("svgAssetSlots");
        for (auto svgAssetSlot: svgAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("svgAssetSlot");
            tempXML.setTo("svgAssetSlot");
            tempXML.addValue("slotName", svgAssetSlot.first);
            tempXML.addValue("assetID", svgAssetSlot.second.first);
            tempXML.addValue("assetBankNo", svgAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (map3DModelAssetSlots.size() > 0) {
        XML.addChild("map3DModelAssetSlots");
        XML.setTo("map3DModelAssetSlots");
        for (auto map3DModelAssetSlot: map3DModelAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("map3DModelAssetSlot");
            tempXML.setTo("map3DModelAssetSlot");
            tempXML.addValue("slotName", map3DModelAssetSlot.first);
            tempXML.addValue("assetID", map3DModelAssetSlot.second.first);
            tempXML.addValue("assetBankNo", map3DModelAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (cubeAssetSlots.size() > 0) {
        XML.addChild("cubeAssetSlots");
        XML.setTo("cubeAssetSlots");
        for (auto cubeAssetSlot: cubeAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("cubeAssetSlot");
            tempXML.setTo("cubeAssetSlot");
            tempXML.addValue("slotName", cubeAssetSlot.first);
            tempXML.addValue("assetID", cubeAssetSlot.second.first);
            tempXML.addValue("assetBankNo", cubeAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    if (fontAssetSlots.size() > 0) {
        XML.addChild("fontAssetSlots");
        XML.setTo("fontAssetSlots");
        for (auto fontAssetSlot: fontAssetSlots) {
            ofXml tempXML;
            tempXML.addChild("fontAssetSlot");
            tempXML.setTo("fontAssetSlot");
            tempXML.addValue("slotName", fontAssetSlot.first);
            tempXML.addValue("assetID", fontAssetSlot.second.first);
            tempXML.addValue("assetBankNo", fontAssetSlot.second.second);
            XML.addXml(tempXML);
        }
        XML.setToParent();
    };
    // add parameters
    XML.serialize(parameters);
    return XML;
}

bool TXModuleBase::loadXMLData(ofXml & XML) {
    bool isValid = false;
    string slotName;
    int moduleID, assetID, assetBankNo;
    
    if(XML.getValue<int>("moduleID") == moduleID) {
        isValid = true;
        
        // add slots
        if(XML.exists("extImageModuleSlots")) {
            XML.setTo("extImageModuleSlots");
            if(XML.exists("extImageModuleSlot"))
            {
                XML.setTo("extImageModuleSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    moduleID = XML.getValue<int>("moduleID");
                    setExtImageModuleSlot(slotName, moduleID);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("imageAssetSlots")) {
            XML.setTo("imageAssetSlots");
            if(XML.exists("imageAssetSlot"))
            {
                XML.setTo("imageAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    setImageAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("movieAssetSlots")) {
            XML.setTo("movieAssetSlots");
            if(XML.exists("movieAssetSlot"))
            {
                XML.setTo("movieAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    setMovieAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("svgAssetSlots")) {
            XML.setTo("svgAssetSlots");
            if(XML.exists("svgAssetSlot"))
            {
                XML.setTo("svgAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    setSvgAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("map3DModelAssetSlots")) {
            XML.setTo("map3DModelAssetSlots");
            if(XML.exists("map3DModelAssetSlot"))
            {
                XML.setTo("map3DModelAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    set3DModelAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("cubeAssetSlots")) {
            XML.setTo("cubeAssetSlots");
            if(XML.exists("cubeAssetSlot"))
            {
                XML.setTo("cubeAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    setCubeAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        if(XML.exists("fontAssetSlots")) {
            XML.setTo("fontAssetSlots");
            if(XML.exists("fontAssetSlot"))
            {
                XML.setTo("fontAssetSlot[0]");
                do {
                    slotName = XML.getValue<string>("slotName");
                    assetID = XML.getValue<int>("assetID");
                    assetBankNo = XML.getValue<int>("assetBankNo");
                    setFontAssetSlot(slotName, assetID, assetBankNo);
                }
                while( XML.setToSibling() );
                XML.setToParent();
            };
            XML.setToParent();
        };
        // add parameters
        XML.deserialize(parameters);
    };
    return isValid;
}

void TXModuleBase::printModuleParameters() {
    ofLogNotice() << "/* ---------- TXV Settable Parameter list for: " << parameters.getName() << " ---------- */";
    ofLogNotice() << "/* GROUP:     [groupType, address, parameters] */";
    ofLogNotice() << "/* PARAMETER: [parameterType, address, val, ?min, ?max] */";
    printMovieAssetSlots();
    printImageAssetSlots();
    printExtImageModuleSlots();
    printSvgAssetSlots();
    print3DModelAssetSlots();
    printCubeAssetSlots();
    printFontAssetSlots();
    printParameterGroup(parameters);
}

void TXModuleBase::printMovieAssetSlots() {
    map<string, pair<int, int> >::iterator iter = movieAssetSlots.begin();
    for (iter=movieAssetSlots.begin(); iter!=movieAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/movie\"";
        string name = "assetSlot/movie/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::printImageAssetSlots() {
    map<string, pair<int, int> >::iterator iter = imageAssetSlots.begin();
    for (iter=imageAssetSlots.begin(); iter!=imageAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/image\"";
        string name = "assetSlot/image/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::printExtImageModuleSlots() {
    map<string, int>::iterator iter = extImageModuleSlots.begin();
    for (iter=extImageModuleSlots.begin(); iter!=extImageModuleSlots.end(); ++iter)
    {
        string typeString = "\"extImageModuleSlot\"";
        string name = "extImageModuleSlot/" + iter->first;
        int moduleID = iter->second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << moduleID << "],";
    };
}

void TXModuleBase::printSvgAssetSlots() {
    map<string, pair<int, int> >::iterator iter = svgAssetSlots.begin();
    for (iter=svgAssetSlots.begin(); iter!=svgAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/svg\"";
        string name = "assetSlot/svg/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::print3DModelAssetSlots() {
    map<string, pair<int, int> >::iterator iter = map3DModelAssetSlots.begin();
    for (iter=map3DModelAssetSlots.begin(); iter!=map3DModelAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/3DModel\"";
        string name = "assetSlot/3DModel/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::printCubeAssetSlots() {
    map<string, pair<int, int> >::iterator iter = cubeAssetSlots.begin();
    for (iter=cubeAssetSlots.begin(); iter!=cubeAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/cube\"";
        string name = "assetSlot/cube/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::printFontAssetSlots() {
    map<string, pair<int, int> >::iterator iter = fontAssetSlots.begin();
    for (iter=fontAssetSlots.begin(); iter!=fontAssetSlots.end(); ++iter)
    {
        string typeString = "\"assetSlot/font\"";
        string name = "assetSlot/font/" + iter->first;
        int assetID = iter->second.first;
        int assetBankNo = iter->second.second;
        ofLogNotice() << "[" << typeString << ", \"" << name << "\", " << assetID << "],";
    };
}

void TXModuleBase::printParameterGroup(ofParameterGroup groupArg, string prefixArg) {
    for(int i=0;i<groupArg.size();i++) {
        string typeString = "";
        string valString = "";
        string minString = "";
        string gapString = "";
        string maxString = "";
        string quoteString = "\"";
        string type = groupArg.getType(i);
        string address = prefixArg;
        const vector<string> hierarchy = groupArg.get(i).getGroupHierarchyNames();
        for(int i=0;i<(int)hierarchy.size()-1;i++){
            address+=hierarchy[i] + "/";
        };
        if (type==typeid(ofParameterGroup).name()) {
            ofParameterGroup holdGroup = groupArg.getGroup(i);
            string firstItemType = holdGroup.getType(0);
            string groupType = "parameterGroup";
            // check if float256
            if (holdGroup.size() == 256) {
                typeString = "\"float256\"";
                valString = "";
                for(int i=0; i<256; i++) {
                    float holdVal = holdGroup.getFloat(i);
                    ofParameter<float> bval = holdGroup.getFloat(i);
                    valString = valString + bval.toString() + ", ";
                };
                ofLogNotice() << "    [" << typeString << ", \"" << address +groupArg.getName(i) << "\", " << valString << "],";
            } else {
                // else check if modParameterGroup
                if (firstItemType == typeid(ofParameter<int>).name()) {
                    groupType = "modParameterGroupInt";
                }else if (firstItemType == typeid(ofParameter<float>).name()) {
                    groupType = "modParameterGroupFloat";
                }else if (firstItemType == typeid(ofParameter<bool>).name()) {
                    groupType = "modParameterGroupBool";
                };
                if (groupType == "parameterGroup") {
                    ofLogNotice() << "[ \"groupStart\", \"" << address + holdGroup.getName() << "\"],";
                    printParameterGroup(holdGroup);
                    ofLogNotice() << "[ \"groupEnd\", \"" << address + holdGroup.getName() << "\"],";
                } else {
                    // for modParameterGroups
                    ofLogNotice() << "[ \"" << groupType << "\", \"" << address + holdGroup.getName() << "\", [";
                    // printParameterGroup(holdGroup, address); // OLD, address prefix no longer needed
                    printParameterGroup(holdGroup);
                    ofLogNotice() << "]],";
                };
            };
        } else {
            bool toBePrinted = true;
            if (type == typeid(ofParameter<int>).name()) {
                typeString = "\"int\"";
                ofParameter<int> ival = groupArg.getInt(i);
                ofParameter<int> imin = ival.getMin();
                ofParameter<int> imax = ival.getMax();
                valString = ival.toString();
                minString = imin.toString();
                gapString = ", ";
                maxString = imax.toString();
            }else if (type == typeid(ofParameter<float>).name()) {
                typeString = "\"float\"";
                ofParameter<float> fval = groupArg.getFloat(i);
                ofParameter<float> fmin = fval.getMin();
                ofParameter<float> fmax = fval.getMax();
                valString = fval.toString();
                minString = fmin.toString();
                gapString = ", ";
                maxString = fmax.toString();
            }else if (type == typeid(ofParameter<bool>).name()) {
                typeString = "\"bool_int\"";
                ofParameter<bool> bval = groupArg.getBool(i);
                valString = bval.toString();
            }else if (type == typeid(ofParameter<string>).name()) {
                typeString = "\"string\"";
                valString =  quoteString + groupArg.getString(i).toString() + quoteString;
            } else {
                //                   typeString = "OtherType";
                toBePrinted = false;
            };
            if (groupArg.getName(i) == "") {
                toBePrinted = false;
            };;
            if (toBePrinted) {
                ofLogNotice() << "    [" << typeString << ", \"" << address +groupArg.getName(i) << "\", " << valString << gapString << minString << gapString << maxString << "],";
            };
        }
    };
}

void TXModuleBase::printModuleOutputs() {
    string holdName;
    ofLogNotice() << "/* ---------- TXV Outputs list for: " << parameters.getName() << " ---------- */";
    map<string, ofPtr <TXModSource> >::iterator iter2 = modSources.begin();
    for (iter2=modSources.begin(); iter2!=modSources.end(); ++iter2)
    {
        holdName = iter2->second->getName();
        ofLogNotice() << "    \"" << holdName << "\", ";
    }
}

////////////////////////////////

void TXModuleBase::createImageAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    imageAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::setImageAssetSlot(string slotNameArg, int imageAssetIDArg, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = imageAssetSlots.find(slotNameArg);
    if (iter == imageAssetSlots.end()) {
        ofLogNotice() << "!!!Warning Asset Slot Not Found: ";
        ofLogNotice() << "TXModuleBase::setImageAssetSlot - slotNameArg, imageAssetID, assetBankNo: " << slotNameArg << ", " << imageAssetIDArg << ", " << assetBankNoArg;        
        return false;
    };
    imageAssetSlots[slotNameArg].first = imageAssetIDArg;
    imageAssetSlots[slotNameArg].second = assetBankNoArg;
    imageAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::getImageAssetIDSlot(string slotNameArg) {
    return imageAssetSlots[slotNameArg];
}

void TXModuleBase::removeImageAssetReferences(int imageAssetIDArg) {
    map<string, pair<int, int> >::iterator iter = imageAssetSlots.begin();
    for (iter=imageAssetSlots.begin(); iter!=imageAssetSlots.end(); ++iter)
    {
        if (iter->second.first == imageAssetIDArg) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::imageAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::createMovieAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    movieAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::setMovieAssetSlot(string slotNameArg, int movieAssetIDArg, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = movieAssetSlots.find(slotNameArg);
    if (iter == movieAssetSlots.end()) {
        return false;
    }
    movieAssetSlots[slotNameArg].first = movieAssetIDArg;
    movieAssetSlots[slotNameArg].second = assetBankNoArg;
    movieAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::getMovieAssetIDSlot(string slotNameArg) {
    return movieAssetSlots[slotNameArg];
}

void TXModuleBase::removeMovieAssetReferences(int movieAssetIDArg) {
    map<string, pair<int, int> >::iterator iter = movieAssetSlots.begin();
    for (iter=movieAssetSlots.begin(); iter!=movieAssetSlots.end(); ++iter)
    {
        if (iter->second.first == movieAssetIDArg) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::movieAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::createSvgAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    svgAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::setSvgAssetSlot(string slotNameArg, int svgAssetIDArg, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = svgAssetSlots.find(slotNameArg);
    if (iter == svgAssetSlots.end()) {
        return false;
    }
    svgAssetSlots[slotNameArg].first = svgAssetIDArg;
    svgAssetSlots[slotNameArg].second = assetBankNoArg;
    svgAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::getSvgAssetIDSlot(string slotNameArg) {
    return svgAssetSlots[slotNameArg];
}

void TXModuleBase::removeSvgAssetReferences(int svgAssetIDArg) {
    map<string, pair<int, int> >::iterator iter = svgAssetSlots.begin();
    for (iter=svgAssetSlots.begin(); iter!=svgAssetSlots.end(); ++iter)
    {
        if (iter->second.first == svgAssetIDArg) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::svgAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::create3DModelAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    map3DModelAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::set3DModelAssetSlot(string slotNameArg, int arg3DModelAssetID, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = map3DModelAssetSlots.find(slotNameArg);
    if (iter == map3DModelAssetSlots.end()) {
        return false;
    }
    map3DModelAssetSlots[slotNameArg].first = arg3DModelAssetID;
    map3DModelAssetSlots[slotNameArg].second = assetBankNoArg;
    a3DModelAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::get3DModelAssetIDSlot(string slotNameArg) {
    return map3DModelAssetSlots[slotNameArg];
}

void TXModuleBase::remove3DModelAssetReferences(int arg3DModelAssetID) {
    map<string, pair<int, int> >::iterator iter = map3DModelAssetSlots.begin();
    for (iter=map3DModelAssetSlots.begin(); iter!=map3DModelAssetSlots.end(); ++iter)
    {
        if (iter->second.first == arg3DModelAssetID) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::a3DModelAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::createCubeAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    cubeAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::setCubeAssetSlot(string slotNameArg, int cubeAssetIDArg, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = cubeAssetSlots.find(slotNameArg);
    if (iter == cubeAssetSlots.end()) {
        return false;
    }
    cubeAssetSlots[slotNameArg].first = cubeAssetIDArg;
    cubeAssetSlots[slotNameArg].second = assetBankNoArg;
    cubeAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::getCubeAssetIDSlot(string slotNameArg) {
    return cubeAssetSlots[slotNameArg];
}

void TXModuleBase::removeCubeAssetReferences(int cubeAssetIDArg) {
    map<string, pair<int, int> >::iterator iter = cubeAssetSlots.begin();
    for (iter=cubeAssetSlots.begin(); iter!=cubeAssetSlots.end(); ++iter)
    {
        if (iter->second.first == cubeAssetIDArg) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::cubeAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::createFontAssetSlot(string slotNameArg) {
    std::pair<int, int> dataPair;
    dataPair = std::make_pair (0, 0);
    fontAssetSlots[slotNameArg] = dataPair;
}

bool TXModuleBase::setFontAssetSlot(string slotNameArg, int fontAssetIDArg, int assetBankNoArg) {
    // check asset exists before changing
    map<string, pair<int, int> >::iterator iter = fontAssetSlots.find(slotNameArg);
    if (iter == fontAssetSlots.end()) {
        return false;
    }
    fontAssetSlots[slotNameArg].first = fontAssetIDArg;
    fontAssetSlots[slotNameArg].second = assetBankNoArg;
    fontAssetSlotChanged(slotNameArg);
    return true;
}

pair<int, int> TXModuleBase::getFontAssetIDSlot(string slotNameArg) {
    return fontAssetSlots[slotNameArg];
}

void TXModuleBase::removeFontAssetReferences(int fontAssetIDArg) {
    map<string, pair<int, int> >::iterator iter = fontAssetSlots.begin();
    for (iter=fontAssetSlots.begin(); iter!=fontAssetSlots.end(); ++iter)
    {
        if (iter->second.first == fontAssetIDArg) {
            iter->second.first = 0;
            iter->second.second = 0;
        };
    }
}

void TXModuleBase::fontAssetSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::createExtImageModuleSlot(string slotNameArg) {
    extImageModuleSlots[slotNameArg] = 0;
}

bool TXModuleBase::setExtImageModuleSlot(string slotNameArg, int extImageModuleIDArg) {
    // check asset exists before changing
    map<string, int>::iterator iter = extImageModuleSlots.find(slotNameArg);
    if (iter == extImageModuleSlots.end()) {
        return false;
    }
    extImageModuleSlots[slotNameArg] = extImageModuleIDArg;
    extImageModuleSlotChanged(slotNameArg);
    return true;
}

int TXModuleBase::getExtImageModuleIDSlot(string slotNameArg) {
    return extImageModuleSlots[slotNameArg];
}

void TXModuleBase::removeExtImageModuleReferences(int extImageModuleIDArg) {
    map<string, int>::iterator iter = extImageModuleSlots.begin();
    for (iter=extImageModuleSlots.begin(); iter!=extImageModuleSlots.end(); ++iter)
    {
        if (iter->second == extImageModuleIDArg) {
            iter->second = 0;
        };
    }
}

void TXModuleBase::extImageModuleSlotChanged(string slotNameArg) {
    // override as needed
}

////////////////////////////////

void TXModuleBase::registerTexture() {
    hasTexture = true;
}

ofTexture * TXModuleBase::getTexture(){
    return NULL;
}

int TXModuleBase::getTextureWidth() {
    return 0;
}

int TXModuleBase::getTextureHeight() {
    return 0;
}

ofPixelsRef TXModuleBase::getPixels() {
    ofPixels p;
    return p;
}

