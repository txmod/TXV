// this code is modified from ofxBezierSurface - see changes marked paul

#include "TXBezierSurface.h"

void TXBezierSurface::setup(int w, int h, int dim, int res) {
    width = w;
    height = h;
    cx = dim-1;
    cy = dim-1;
    rx = res;
    ry = res;
    
    int i,j;
    
    // clears added by paul
    inp.clear();
    outp.clear();
    
    // create point vectors
    for (i=0; i<=cx; i++) {
        inp.push_back(vector<ofVec3f>());
        for (j=0; j<=cy; j++) {
            inp[i].push_back(ofVec3f());
        }
    }
    for (i=0; i<rx; i++) {
        outp.push_back(vector<ofVec3f>());
        for (j=0; j<ry; j++) {
            outp[i].push_back(ofVec3f());
        }
    }
    
    // load default points
    for (i=0;i<=cx;i++) {
        for (j=0;j<=cy;j++) {
            inp[i][j].x = ofMap(i, 0, cx, 0, width);
            inp[i][j].y = ofMap(j, 0, cy, 0, height);
            inp[i][j].z = 0;
        }
    }
    
    // create default surface
    
    // mesh replaced with plane by paul
    //mesh = ofMesh::plane(width, height, rx, ry, OF_PRIMITIVE_TRIANGLES);
    plane.set(width, height, rx, ry, OF_PRIMITIVE_TRIANGLES);
    
    createSurface();

    vector<ofVec3f> verts = plane.getMesh().getVertices();
    for (i=0; i<verts.size(); i++) {
        plane.getMesh().setTexCoord(i, ofVec2f(verts[i].x, verts[i].y));
    }
    
    // interface
    updateSurface = false;
    ctrlPntSize = 10;
    up = false;
    down = false;
    left = false;
    right = false;
    found  = false;
}

void TXBezierSurface::draw() {
    plane.draw();
}

void TXBezierSurface::drawWireframe() {
    plane.drawWireframe();
}

void TXBezierSurface::update() {
    if (updateSurface) {
        createSurface();
        updateSurface = false;
    }
}

void TXBezierSurface::drawControls() {
    for (int i=0;i<=cx;i++) {
        for (int j=0;j<=cy;j++) {
            
            for (int k=0;k<selectedPnts.size();k++) {
                if (selectedPnts[k].x == i && selectedPnts[k].y == j) {
                    ofSetColor(200,200,0);
                    break;
                }
                else
                    ofSetColor(200,200,200);
            }
            ofDrawCircle(inp[i][j].x, inp[i][j].y, inp[i][j].z, ctrlPntSize);
        }
    }
}


vector<ofVec3f> TXBezierSurface::getVertices(){
    return plane.getMesh().getVertices();
}

void TXBezierSurface::setVertices(vector<ofVec3f> & verts){
    for (int i=0; i<verts.size(); i++) {
        plane.getMesh().setVertex(i, verts[i]);
    }
}

vector<ofVec3f> TXBezierSurface::getControlPnts(){
    vector<ofVec3f> vec;
    for (int i=0; i<=cx; i++) {
        for (int j=0; j<=cy; j++) {
            vec.push_back(inp[i][j]);
        }
    }
    return vec;
}
void TXBezierSurface::setControlPnts(vector<ofVec3f> vec){
    int c=0;
    for (int i=0; i<=cx; i++) {
        for (int j=0; j<=cy; j++) {
            inp[i][j] = vec[c];
            c++;
        }
    }
    createSurface();
}

int TXBezierSurface::getControlPntDim(){
    return cx+1;
}

void TXBezierSurface::setControlPntDim(int dim){
    int oldcx = cx;
    int oldcy = cy;
    
    cx = dim-1;
    cy = dim-1;
    
    vector< vector<ofVec3f> > oldInp;
    
    for (int i=0;i<=oldcx;i++) {
        oldInp.push_back(vector<ofVec3f>());

        for (int j=0;j<=oldcy;j++) {
            oldInp[i].push_back(ofVec3f());
            oldInp[i][j].x = inp[i][j].x;
            oldInp[i][j].y = inp[i][j].y;
            oldInp[i][j].z = inp[i][j].z;
        }
    }
    
    
    oldInp[1][0].x = inp[1][0].x*.75;
    oldInp[1][1].x = inp[1][1].x*.75;
    oldInp[1][2].x = inp[1][2].x*.75;
    oldInp[1][3].x = inp[1][3].x*.75;

    
    inp.clear();
    
    for (int i=0; i<=cx; i++) {
        inp.push_back(vector<ofVec3f>());
        for (int j=0; j<=cy; j++) {
            inp[i].push_back(ofVec3f());
        }
    }
    
 
    // load default points
    for (int i=0;i<=cx;i++) {
        for (int j=0;j<=cy;j++) {
            inp[i][j].x = ofMap(i, 0, cx, 0, width);
            inp[i][j].y = ofMap(j, 0, cy, 0, height);
            inp[i][j].z = 0;
        }
    }
    
    inp = calculateSurface(oldInp, inp, oldcx, oldcy, cx+1, cy+1);
    
    createSurface();
}

void TXBezierSurface::reset() {
    // load default points
    for (int i=0;i<=cx;i++) {
        for (int j=0;j<=cy;j++) {
            inp[i][j].x = ofMap(i, 0, cx, 0, width);
            inp[i][j].y = ofMap(j, 0, cy, 0, height);
            inp[i][j].z = 0;
        }
    }
    createSurface();
}

void TXBezierSurface::addListeners(){
    ofAddListener(ofEvents().mousePressed, this, &TXBezierSurface::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &TXBezierSurface::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &TXBezierSurface::mouseReleased);
    ofAddListener(ofEvents().keyPressed, this, &TXBezierSurface::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &TXBezierSurface::keyReleased);
}


//----------------------------------------------------- interaction.
void TXBezierSurface::mousePressed(ofMouseEventArgs& mouseArgs) {
    float distance = 0;
    ofPoint tmp;
    bool missing = true;
    
    tmp.set(findPoint(mouseArgs));
    
    if (!ofGetKeyPressed(OF_KEY_SHIFT)) {
        selectedPnts.clear();
    }
    
    for (int i=0; i<selectedPnts.size(); i++) {
        if (selectedPnts[i].x == tmp.x && selectedPnts[i].y == tmp.y)
            missing = false;
    }
    
    if (missing)
        selectedPnts.push_back(tmp);
    
    lastMouse = ofPoint(mouseArgs.x, mouseArgs.y);
}

ofPoint TXBezierSurface::findPoint(ofMouseEventArgs mouseArgs){
    ofPoint pnt;
    float distance = 0;
    float nearest = -1;

    
    for (int i=0; i<=cx; i++) {
        for (int j=0; j<=cy; j++) {
            distance = ofDist(inp[i][j].x, inp[i][j].y, mouseArgs.x, mouseArgs.y);
            if (nearest == -1)
                nearest = distance;
            if (distance < nearest) {
                pnt.set(i,j);
                nearest = distance;
            }
        }
    }
    return pnt;
}

void TXBezierSurface::mouseDragged(ofMouseEventArgs& mouseArgs) {
   if (selectedPnts.size() > 0) {
        ofPoint mouse = ofPoint(mouseArgs.x, mouseArgs.y);
        ofPoint d = ofPoint(mouse.x - lastMouse.x, mouse.y - lastMouse.y);
        for (int i=0; i<selectedPnts.size(); i++) {
            inp[selectedPnts[i].x][selectedPnts[i].y].x += d.x;
            inp[selectedPnts[i].x][selectedPnts[i].y].y += d.y;
        }
        updateSurface = true;
        lastMouse = mouse;
    }
}

void TXBezierSurface::mouseReleased(ofMouseEventArgs& mouseArgs) {
}

void TXBezierSurface::keyPressed(ofKeyEventArgs& keyArgs) {
    int key = keyArgs.key;
    
    float dx=0;
    float dy=0;
    if (key == OF_KEY_UP || key == OF_KEY_DOWN || key == OF_KEY_LEFT || key == OF_KEY_RIGHT ) {
        if (key == OF_KEY_UP) up = true;
        else if (key == OF_KEY_DOWN) down = true;
        else if (key == OF_KEY_LEFT) left = true;
        else if (key == OF_KEY_RIGHT) right = true;
        
        if (up) dy = -1;
        if (down) dy = 1;
        if (left) dx = -1;
        if (right) dx = 1;
        
        if (selectedPnts.size() > 0) {
            for (int i=0; i<selectedPnts.size(); i++) {
                inp[selectedPnts[i].x][selectedPnts[i].y].x += dx;
                inp[selectedPnts[i].x][selectedPnts[i].y].y += dy;
            }
            updateSurface  = true;
        }
    }

}

void TXBezierSurface::keyReleased(ofKeyEventArgs& keyArgs){
    int key = keyArgs.key;
    if (!ofGetKeyPressed(OF_KEY_SHIFT)){
        if (key == OF_KEY_UP) up = false;
        else if (key == OF_KEY_DOWN) down = false;
        else if (key == OF_KEY_LEFT) left = false;
        else if (key == OF_KEY_RIGHT) right = false;
    }
}

//----------------------------------------------------- bezier.
void TXBezierSurface::createSurface() {
    outp = calculateSurface(inp, outp, cx, cy, rx, ry);
    
    int i,j;
    int cnt;
    vector<ofVec3f> verts;
    for (i=0;i<rx;i++) {
        for (j=0;j<ry;j++) {
            verts.push_back(outp[i][j]);
        }
    }
    for (i=0; i<verts.size(); i++) {
        plane.getMesh().setVertex(i, verts[i]);
    }
    calcMeshNormals();
}

void TXBezierSurface::calcMeshNormals(){
    int ia;
    int ib;
    int ic;
    int holdNumIndices = plane.getMesh().getNumIndices();
    int holdNumVertices = plane.getMesh().getNumVertices();
    // reset normals
    for( int i=0; i < plane.getMesh().getVertices().size(); i++ ) plane.getMesh().getNormals()[i] = ofPoint(0,0,0);
    for( int i=0; i < holdNumIndices; i+=3 ){
        ia = plane.getMesh().getIndices()[i];
        ib = plane.getMesh().getIndices()[min(i+1, holdNumIndices-1)];
        ic = plane.getMesh().getIndices()[min(i+2, holdNumIndices-1)];
        ofVec3f e1 = plane.getMesh().getVertices()[ia] - plane.getMesh().getVertices()[ib];
        ofVec3f e2 = plane.getMesh().getVertices()[ic] - plane.getMesh().getVertices()[ib];
        ofVec3f no = e2.cross( e1 );
        plane.getMesh().getNormals()[ia] -= no;
        plane.getMesh().getNormals()[ib] -= no;
        plane.getMesh().getNormals()[ic] -= no;
    }
    //Normalize
    for(int i=0; i < plane.getMesh().getNormals().size(); i++ ) {
        plane.getMesh().getNormals()[i].normalize();
    };
}


vector< vector<ofVec3f> > TXBezierSurface::calculateSurface(vector< vector<ofVec3f> > ip, vector< vector<ofVec3f> > op,
                                                             int cpx, int cpy, int rpx, int rpy ){
    double mui,muj;
    double bi, bj;
    float x,y,z;
    
    // calculate bezier surface
    for (int i=0;i<rpx;i++) {
        mui = i / (double)(rpx-1);
        for (int j=0;j<rpy;j++) {
            muj = j / (double)(rpy-1);
            
            op[i][j].x = 0;
            op[i][j].y = 0;
            op[i][j].z = 0;
            
            for (int ki=0;ki<=cpx;ki++) {
                bi = bezierBlend(ki,mui,cpx);
                for (int kj=0;kj<=cpy;kj++) {
                    bj = bezierBlend(kj,muj,cpy);
                    op[i][j].x += (ip[ki][kj].x * bi * bj);
                    op[i][j].y += (ip[ki][kj].y * bi * bj);
                    op[i][j].z += (ip[ki][kj].z * bi * bj);
                }
            }
        }
    }
    
    return op;
}

double TXBezierSurface::bezierBlend(int k, double mu, int n) {
    int nn,kn,nkn;
    double blend=1;
    
    nn = n;
    kn = k;
    nkn = n - k;
    
    while (nn >= 1) {
        blend *= nn;
        nn--;
        if (kn > 1) {
            blend /= (double)kn;
            kn--;
        }
        if (nkn > 1) {
            blend /= (double)nkn;
            nkn--;
        }
    }
    if (k > 0)
        blend *= pow(mu,(double)k);
    if (n-k > 0)
        blend *= pow(1-mu,(double)(n-k));
    
    return(blend);
}
