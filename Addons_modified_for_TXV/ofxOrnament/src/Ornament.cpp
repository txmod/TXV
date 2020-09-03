/*
 *  Ornament.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

// AMENDED BY PAUL - search for PAUL to see changes

#include "Ornament.h"


//------------------------------------------------------------------
void Ornament::setup(int w, int h, WALLPAPER_GROUP wallpaperGroup_, int tileSize_, float angle_) {
    
    width = w;
    height = h;
    wallpaperGroup = wallpaperGroup_;
    tileSize = tileSize_;
    angle = angle_;
    fbo.allocate(width, height);    
    
    ornamentShader.setupShaderFromSource(GL_VERTEX_SHADER, getVertexShader());
    ornamentShader.setupShaderFromSource(GL_FRAGMENT_SHADER, getOrnamentShader());
    ornamentShader.linkProgram();
    
    
    wallpaperShader.setupShaderFromSource(GL_VERTEX_SHADER, getVertexShader());
    wallpaperShader.setupShaderFromSource(GL_FRAGMENT_SHADER, getWallpaperShader());
    wallpaperShader.linkProgram();
    
}

void Ornament::loadTexture(ofTexture texture){
    inputTexture = texture;
    
    int w = width;
    int h = height;
    if (texture.getWidth() > w) {
        w = texture.getWidth();
    }
    if (texture.getHeight() > h) {
        h = texture.getHeight();
    }
    
    
    if (!tileFbo.isAllocated() || tileFbo.getWidth() != w || tileFbo.getHeight()!=h) {
        tileFbo.allocate(w, h);
        resizeFbo.allocate(w, h);
    }
    createOrnament();
}

void Ornament::setWallpaperGroup(int group){
    setWallpaperGroup((WALLPAPER_GROUP)(group%17));
}

void Ornament::setWallpaperGroup(WALLPAPER_GROUP group){
    wallpaperGroup = group;
    createOrnament();
}

WALLPAPER_GROUP Ornament::getWallpaperGroup(){
    return wallpaperGroup;
}

int Ornament::getWallpaperGroupAsInt(){
    return wallpaperGroup;
}

void Ornament::setTileSize(float t){
    tileSize = t;
}

int Ornament::getTileSize(){
    return tileSize;
}

void Ornament::setAngle(float angleRad){
    angle = angleRad;
}

float Ornament::getAngle(){
    return angle;
}

// ADDED BY PAUL ================
void Ornament::setInputZoomX(float argFloat){
    inputZoomX = argFloat;
}

float Ornament::getInputZoomX(){
    return inputZoomX;
}

void Ornament::setInputZoomY(float argFloat){
    inputZoomY = argFloat;
}

float Ornament::getInputZoomY(){
    return inputZoomY;
}

void Ornament::setInputShiftX(float argFloat){
    inputShiftX = argFloat;
}

float Ornament::getInputShiftX(){
    return inputShiftX;
}

void Ornament::setInputShiftY(float argFloat){
    inputShiftY = argFloat;
}

float Ornament::getInputShiftY(){
    return inputShiftY;
}

void Ornament::setInputRotate(float argFloat){
    inputRotate = argFloat;
}

float Ornament::getInputRotate(){
    return inputRotate;
}
// END OF ADDED BY PAUL ================


void Ornament::createOrnament(){
    tile = TileFactory::createTile(wallpaperGroup);
    //tile->setup(width,height);
    tile->setup(inputTexture.getWidth(),inputTexture.getHeight());
    update();
}

//------------------------------------------------------------------
void Ornament::update() {
    //resize texture
    resizeFbo.begin();
    ofClear(0, 0, 0, 0);
    ofVec2f pNew, sizeNew;
    getBoundingBox(tile->getOrnamentBase(),pNew,sizeNew);
    //toTextureSpace(pNew);
    //toTextureSpace(sizeNew);
    ofVec2f sizeTex = resize(ofVec2f(inputTexture.getWidth(),inputTexture.getHeight()), sizeNew);
    ofVec2f posTex = (pNew + sizeNew*0.5) - sizeTex*0.5;
    
    // CHANGED BY PAUL ================
    // OLD:
    //inputTexture.draw(posTex.x,posTex.y,sizeTex.x,sizeTex.y);
    // NEW:
    ofVec2f halfSizeTex = sizeTex * 0.5;
    if (!inputTexture.isAllocated()) {
        return;
    };
    ofPushMatrix();
     // move to center
    // apply zoom, shift, rotate
    ofTranslate(posTex.x, posTex.y);
    ofTranslate(halfSizeTex.x, halfSizeTex.y);
    ofScale(inputZoomX, inputZoomY);
    ofRotate(inputRotate);
    ofTranslate(inputShiftX * halfSizeTex.x, inputShiftY * halfSizeTex.x);
    // draw
    inputTexture.draw(-halfSizeTex.x, -halfSizeTex.y, sizeTex.x, sizeTex.y);
    ofPopMatrix();
    // END OF CHANGED BY PAUL ================
    
    resizeFbo.end();
    
    //create tile
    tileFbo.begin();
    ofClear(0, 0, 0, 0);
    ornamentShader.begin();
    ornamentShader.setUniform1i("cell_structure", tile->getCellStructure() );
    ornamentShader.setUniform1i("wallpaper_group", wallpaperGroup );
    ornamentShader.setUniform1f("width", inputTexture.getWidth() );
    ornamentShader.setUniform1f("height", inputTexture.getHeight() );
    resizeFbo.draw(0,0);
    
    ornamentShader.end();
    tileFbo.end();
    
    //create wallpaper
    fbo.begin();
    ofClear(255,255,255, 0);
    ofSetColor(255,255,255, 255);
    wallpaperShader.begin();
    wallpaperShader.setUniform1i("cell_structure", tile->getCellStructure() );
    wallpaperShader.setUniform1f("width", width );
    wallpaperShader.setUniform1f("height", height );
    wallpaperShader.setUniform1f("tile_size", tileSize );
    wallpaperShader.setUniform1f("angle", angle );
    wallpaperShader.setUniform1f("tex_width", inputTexture.getWidth() );
    wallpaperShader.setUniform1f("tex_height",inputTexture.getHeight() );
    tileFbo.draw(0, 0);
    wallpaperShader.end();
    fbo.end();
    
    outputTexture = fbo.getTexture();
    //outputTexture = tileFbo.getTexture();
    
    tile->updateTile();
}

void Ornament::setCellStructure(int s){
    tile->setCellStructure(s);
    update();
}

int Ornament::getCellStructure(){
    return tile->getCellStructure();
}

//------------------------------------------------------------------
///\ draw the ornament
void Ornament::draw(int x, int y) {
    outputTexture.draw(x, y);
}

void Ornament::drawDebug(int x, int y, int w, int h ){
    if (w == -1) {
        w = inputTexture.getWidth();
    }
    if (h == -1){
        h = inputTexture.getHeight();
    }
    
    
    ofPushMatrix();
    ofTranslate(x, y);
    //texture
    ofVec2f pNew, sizeNew;
    getBoundingBox(tile->getOrnamentBase(),pNew,sizeNew);
    
    ofVec2f sizeTex = resize(ofVec2f(inputTexture.getWidth(),inputTexture.getHeight()), sizeNew);
    ofVec2f posTex = (pNew + sizeNew*0.5) - sizeTex*0.5;
    ofVec2f scaleFactor = ofVec2f(w,h)/sizeTex;
    
    sizeTex*=scaleFactor;
    
    inputTexture.draw(0,0,sizeTex.x,sizeTex.y);
    
    //bounding box
    vector<ofVec2f> base = tile->getOrnamentBase();
    for (auto& point : base) {
        point -= posTex;
        point *= scaleFactor;
    }
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofBeginShape();
    for (auto point : base) {
        ofVertex(point.x,point.y);
    }
    ofVertex(base[0].x,base[0].y);
    ofEndShape();
    ofSetColor(255);
    
    ofPopMatrix();
}

ofTexture& Ornament::getTexture(){
    return outputTexture;
}

vector<ofVec2f> Ornament::getOrnamentBase(){
    return tile->getOrnamentBase();
}

vector<ofVec2f> Ornament::getTilePoly(){
    return tile->getTilePoly();
}

string Ornament::getVertexShader(){
    string out = string("#version 120\n") +
    STRINGIFY(
              void main() {
                  gl_TexCoord[0] = gl_MultiTexCoord0;
                  gl_Position = ftransform();
              }
              );
    return out;
}

string Ornament::getOrnamentShader(){
    string out = string("#version 120\n#extension GL_ARB_texture_rectangle : enable\n#define PI 3.141592653589793\n#define P4 9\n#define P4M 10\n#define P4G 11\n#define P3 12\n#define P3M1 13\n#define P31M 14\n#define P6 15\n#define P6mm 16\n") +
    STRINGIFY(
              uniform sampler2DRect 	u_tex_unit0;
              uniform float 			width,height;
              uniform int 			wallpaper_group;
              /*
               0 = P1,
               1 = P2,
               2 = PM,
               3 = PG,
               4 = CM,
               5 = PMM,
               6 = PMG,
               7 = PGG,
               8 = CMM
               */
              uniform int 			cell_structure;
              /*
               0 = RECTANGLE,
               1 = SQUARE,
               2 = RHOMBIC,
               3 = HEXAGONAL,
               4 = OBLIQUE
               */
              
              
              vec2 p1,p2,p3,p4;
              vec2 base1,base2,base3,base4,mid;
              vec2 p1p2, p2p3, p3p4, p1p4;
              
              /*****************
               * Transformation *
               ******************/
              vec2 translate(vec2 point ,vec2 trans){
                  return point + trans;
              }
              
              vec2 rotate(vec2 point, float angle){
                  mat2 rot = mat2 (
                                   cos(angle), sin(angle),
                                   -sin(angle),cos(angle));
                  return rot * point;
              }
              
              vec2 rotateAt(vec2 point, vec2 anchor, float angle){
                  return vec2(
                              cos(angle)*point.x - sin(angle)*point.y + anchor.x - cos(angle)*anchor.x + sin(angle)*anchor.y,
                              sin(angle)*point.x + cos(angle)*point.y + anchor.y - sin(angle)*anchor.x - cos(angle)*anchor.y);
              }
              
              vec2 reflectAt(vec2 point, vec2 anchor, vec2 dir){
                  vec2 I = point-anchor;
                  vec2 N = normalize(dir);
                  vec2 r = reflect(I,N);
                  return anchor - r;
              }
              
              
              /************************
               * Position calculation *
               ************************/
              void getBorders(){
                  if (cell_structure == 1){
                      float lengthCell = min(width, height);
                      p1 = vec2((width-lengthCell)/2, (height-lengthCell)/2);
                      p2 = vec2((width-lengthCell)/2 + lengthCell, (height-lengthCell)/2);
                      p3 = vec2((width-lengthCell)/2 + lengthCell, (height-lengthCell)/2 + lengthCell);
                      p4 = vec2((width-lengthCell)/2, (height-lengthCell)/2 + lengthCell);
                  }
                  else if (cell_structure == 3){
                      float hmax = width*sqrt(3)/3;
                      float wmax = width;
                      
                      if (hmax>height) {
                          hmax = height;
                          wmax = hmax*3/sqrt(3);
                      }
                      
                      p1 = vec2(wmax*1/3,0);
                      p2 = vec2(wmax,0);
                      p3 = vec2(wmax*2/3,hmax);
                      p4 = vec2(0,hmax);
                  }
                  
              }
              bool PointInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2)
              {
                  float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
                  float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;
                  
                  if ((s < 0) != (t < 0))
                      return false;
                  
                  float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;
                  if (A < 0.0)
                  {
                      s = -s;
                      t = -t;
                      A = -A;
                  }
                  return s > -0.01 && t > -0.01 && (s + t) < A;
              }
              
              bool isInTile(vec2 p)
              {
                  //pt resolves edge jitter
                  vec2 pt = vec2(p.x-0.1,p.y-0.1);
                  if(PointInTriangle(p,p1,p2,p4) || PointInTriangle(p,p2,p3,p4)
                     ||PointInTriangle(pt,p1,p2,p4) || PointInTriangle(pt,p2,p3,p4)){
                      return true;
                  }
                  return false;
              }
              
              //type 0=P4, 1=P4M, 2=P4G
              int getTileSquare(vec2 pos,int type){
                  //ornament base
                  mid = p1 + (p3-p1)/2;
                  p1p2 = p1 + (p2-p1)/2;
                  p2p3 = p2 + (p3-p2)/2;
                  p3p4 = p3 + (p4-p3)/2;
                  p1p4 = p1 + (p4-p1)/2;
                  
                  int t1,t2;
                  
                  if(PointInTriangle(pos,p1,p1p2,mid)){
                      t1 = 0;
                      if(PointInTriangle(pos,p1,p1p2,p1 + (mid-p1)/2)){
                          t2 = 0;
                      }
                      else{
                          t2 = 1;
                      }
                  }
                  else if(PointInTriangle(pos,p1,mid,p1p4)){
                      t1 = 0;
                      if(PointInTriangle(pos,p1,p1p4,p1 + (mid-p1)/2)){
                          t2 = 2;
                      }
                      else{
                          t2 = 3;
                      }
                  }
                  else if(PointInTriangle(pos,p1p2,p2,p2p3)){
                      t1 = 1;
                      if(PointInTriangle(pos,p1p2,p2,p2 + (mid-p2)/2)){
                          t2 = 0;
                      }
                      else{
                          t2 = 1;
                      }
                  }
                  else if(PointInTriangle(pos,p1p2,p2p3,mid)){
                      t1 = 1;
                      if(PointInTriangle(pos,p1p2,mid,p2 + (mid-p2)/2)){
                          t2 = 2;
                      }
                      else{
                          t2 = 3;
                      }
                  }
                  else if(PointInTriangle(pos,mid,p2p3,p3)){
                      t1 = 2;
                      if(PointInTriangle(pos,mid,p2p3,p2p3 + (p3p4-p2p3)/2)){
                          t2 = 0;
                      }
                      else{
                          t2 = 1;
                      }
                  }
                  else if(PointInTriangle(pos,mid,p3,p3p4)){
                      t1 = 2;
                      if(PointInTriangle(pos,mid,p3p4,p3p4 + (p2p3-p3p4)/2)){
                          t2 = 2;
                      }
                      else{
                          t2 = 3;
                      }
                  }
                  else if(PointInTriangle(pos,p1p4,mid,p3p4)){
                      t1 = 3;
                      if(PointInTriangle(pos,mid,p1p4,p1p4 + (p3p4-p1p4)/2)){
                          t2 = 0;
                      }
                      else{
                          t2 = 1;
                      }
                  }
                  else{
                      t1 = 3;
                      if(PointInTriangle(pos,p4,p3p4,p1p4 + (p3p4-p1p4)/2)){
                          t2 = 2;
                      }
                      else{
                          t2 = 3;
                      }
                  }
                  
                  int t = t1*4 + t2;
                  //return t1;
                  
                  int lut[16];
                  if(type == 0){
                      // 00 01 02 03 10 11 12 13 20 21 22 23 30 31 32 33
                      lut = int[16]( 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3);
                  }else if(type == 1){
                      // 00 01 02 03  10  11  12  13  20  21  22  23  30  31  32  33
                      lut = int[16]( 0, 0, 1, 1, 10, 11, 10, 11, 20, 20, 21, 21, 30, 31, 31, 30);
                  }
                  else if(type == 2){
                      // 00 01 02 03  10  11  12  13  20  21  22  23  30  31  32  33
                      lut = int[16]( 1, 0, 1, 0, 11, 11, 10, 10, 21, 20, 21, 20, 31, 31, 30, 30);
                  }
                  return lut[t];
              }
              
              int getTileTriangle(vec2 pos,int type){
                  //ornament base
                  base1 = p1;
                  vec2 p1p2 = p1 + (p2-p1)/2;
                  base2 = p1p2 + (p3-p1p2)/3;
                  base3 = p3;
                  vec2 p1p4 = p1 + (p4-p1)/2;
                  base4 = p1p4 + (p3-p1p4)/3;
                  
                  int t1,t2,t3;
                  
                  if(PointInTriangle(pos,p1,p3,p4)){
                      t1 = 0;
                      if(PointInTriangle(pos,p1,p3,base4)){
                          t2 = 0;
                          if (PointInTriangle(pos,p1,p1 + (p3-p1)/2,base4)) t3 = 0;
                          else t3 = 1;
                      }else if(PointInTriangle(pos,p4,p3,base4)){
                          t2 = 1;
                          if (PointInTriangle(pos,p3,p4 + (p3-p4)/2,base4)) t3 = 0;
                          else t3 = 1;
                      }
                      else{
                          t2 = 2;
                          if (PointInTriangle(pos,p4,p4 + (p1-p4)/2,base4)) t3 = 0;
                          else t3 = 1;
                      }
                  }else{
                      t1 = 1;
                      if(PointInTriangle(pos,p1,p3,base2)){
                          t2 = 0;
                          if (PointInTriangle(pos,p1,p1 + (p3-p1)/2,base2)) t3 = 0;
                          else t3 = 1;
                      }else if(PointInTriangle(pos,p1,p2,base2)){
                          t2 = 1;
                          if (PointInTriangle(pos,p2,p1 + (p2-p1)/2,base2)) t3 = 0;
                          else t3 = 1;
                      }
                      else{
                          t2 = 2;
                          if (PointInTriangle(pos,p3,p3 + (p2-p3)/2,base2)) t3 = 0;
                          else t3 = 1;
                      }
                  }
                  int t = t1*6 + t2*2 + t3;
                  
                  int lut[12];
                  if(type == 0){
                      // 000 001 010 011 020 021 100 101 110 111 120 121
                      lut = int[12]( 0,  0,  3,  3,  4,  4,  0,  0,  1,  1,  2,  2);
                  }else if(type == 1){
                      // 000 001 010 011 020 021 100 101 110 111 120 121
                      lut = int[12]( 0,  1, 31, 30, 40, 41,  0,  1, 11, 10,  20, 21);
                  }else if(type == 2 || type == 3){
                      // 000 001 010 011 020 021 100 101 110 111 120 121
                      lut = int[12]( 0,  0,  4,  4,  5,  5,  1,  1,  2,  2,  3,  3);
                  }else if(type == 4){
                      // 000 001 010 011 020 021 100 101 110 111 120 121
                      lut = int[12]( 0,  1,  40,  41,  50,  51,  10,  11,  20,  21,  30,  31);
                  }
                  
                  return lut[t];
              }
              /*************************************
               * WALLPAPER RENDERING  P4 Groups*
               ************************************/
              void do_p4(vec2 pos)
              {
                  int s = getTileSquare(pos, 0);
                  
                  
                  
                  if (s == 0){
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (s == 1){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,-PI*0.5) );
                  }
                  else if (s == 2){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
                  }
                  else if (s == 3){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5) );
                      
                  }
                  else{
                      gl_FragColor = vec4(1,0,0,1);
                  }
              }
              
              void do_p4m(vec2 pos)
              {
                  int s = getTileSquare(pos, 1);
                  
                  if (s == 0){
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (s == 1){
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
                  }
                  else if (s == 10){
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt(pos,p1p2,mid-p1p2) );
                  }
                  else if (s == 11){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*1.5) );
                  }
                  else if (s == 20){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(reflectAt(pos,p1p2,mid-p1p2),mid,PI*0.5));
                  }
                  else if (s == 21){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
                  }
                  else if (s == 30){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5));
                  }
                  else if (s == 31){
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1p4,mid - p1p4) );
                  }
              }
              
              void do_p4g(vec2 pos)
              {
                  int s = getTileSquare(pos, 2);
                  
                  if (s == 0){
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (s == 1){
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1p2,p1p4-p1p2) );
                  }
                  else if (s == 10){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(pos,mid,PI*1.5) );
                  }
                  else if (s == 11){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(reflectAt(pos,p1p2,p2p3-p1p2),mid,PI*1.5) );
                  }
                  else if (s == 20){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (reflectAt (pos,p2p3,p3p4-p2p3),mid,PI) );
                  }
                  else if (s == 21){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
                  }
                  else if (s == 30){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (reflectAt (pos,p1p4,p3p4-p1p4),mid,PI*0.5));
                  }
                  else if (s == 31){
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5)  );
                  }
              }
              
              /*************************************
               * WALLPAPER RENDERING  P3, P6 Groups*
               ************************************/
              void do_p3(vec2 pos)
              {
                  int p = getTileTriangle(pos,0);
                  if (p==0){
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (p==1) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,-2*PI/3) );
                  }
                  else if (p==2) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,2*PI/3) );
                  }
                  else if (p==3) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
                  }
                  else if (p==4) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
                  }
              }
              
              void do_p3m1(vec2 pos)
              {
                  int p = getTileTriangle(pos,1);
                  if (p==0){ 
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (p==1){ 
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,base4,base2-base4) );
                  }
                  else if (p==10) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,-2*PI/3),base4,base2-base4) );
                  }
                  else if (p==11) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,-2*PI/3) );
                  }
                  else if (p==20) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,2*PI/3) );
                  }
                  else if (p==21) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,2*PI/3),base4,base2-base4) );
                  }
                  else if (p==30) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4,-2*PI/3),base4,base2-base4) );
                  }
                  else if (p==31) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
                  }
                  else if (p==40) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
                  }
                  else if (p==41) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4,2*PI/3),base4,base2-base4) );
                  }
              }
              
              void do_p31m(vec2 pos)
              {
                  int p = getTileTriangle(pos,2);
                  if (p==0){ 
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (p==1) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
                  }
                  else if (p==2) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,-2*PI/3),p1,p3-p1) );
                  }
                  else if (p==3) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,2*PI/3),p1,p3-p1) );
                  }
                  else if (p==4) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
                  }
                  else if (p==5) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
                  }
              }
              
              void do_p6(vec2 pos)
              {
                  int p = getTileTriangle(pos,3);
                  if (p==0){ 
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (p==1) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,p1 + (p3-p1)/2, PI) );
                  }
                  else if (p==2) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3) );
                  }
                  else if (p==3) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3) );
                  }
                  else if (p==4) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, 4*PI/3) );
                  }
                  else if (p==5) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, PI-PI/3) );
                  }
              }
              
              void do_p6mm(vec2 pos)
              {
                  int p = getTileTriangle(pos,4);
                  if (p==0){ 
                      gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  }
                  else if (p==1) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p4,p2-p4) );
                  }
                  else if (p==10) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
                  }
                  else if (p==11) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,p1 + (p3-p1)/2, PI) );
                  }
                  else if (p==20) {
                      //fixes transparent point in middle
                      vec2 p1p2 = p1 + (p2-p1)/2;
                      base2 = p1p2 + (p3-p1p2)/3;
                      if(pos.x < p2.x-p1.x +1 && pos.y > base2.y -1) pos += vec2(0,-0.5);
                      
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3),p4,p2-p4) );
                  }
                  else if (p==21) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3) );
                  }
                  else if (p==30) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3),p4,p2-p4) );
                  }
                  else if (p==31) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3) );
                  }
                  else if (p==40) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, 4*PI/3) );
                  }
                  else if (p==41) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4, 4*PI/3),p4,p2-p4) );
                  }
                  else if (p==50) {
                      gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, PI-PI/3) );
                  }
                  else if (p==51) {
                      gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4, PI-PI/3),p4,p2-p4) );
                  }
              }
              
              void main( void )
              {
                  getBorders();
                  
                  vec4 color = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  vec2 pos = gl_TexCoord[0].st;
                  
                  
                  
                  //gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,vec2(width/2,height/2),cos(u_time) ));
                  if(isInTile(pos)){
                      if (wallpaper_group == P4) do_p4(pos);
                      else if (wallpaper_group == P4M) do_p4m(pos);
                      else if (wallpaper_group == P4G) do_p4g(pos);
                      else if (wallpaper_group == P3) do_p3(pos);
                      else if (wallpaper_group == P3M1) do_p3m1(pos);
                      else if (wallpaper_group == P31M) do_p31m(pos);
                      else if (wallpaper_group == P6) do_p6(pos);
                      else if (wallpaper_group == P6mm) do_p6mm(pos);
                      
                  }else{
                      gl_FragColor = vec4(0.0,0.0,0.0,0.0);
                  }
                  
                  
              }              );
    return out;
}

string Ornament::getWallpaperShader(){
    string out = string("#version 120\n#extension GL_ARB_texture_rectangle : enable\n#define PI 3.141592653589793\n#define RECTANGLE 0\n#define SQUARE 1\n#define RHOMBIC 2\n#define HEXAGONAL 3\n#define OBLIQUE 4\n") +
    STRINGIFY(uniform sampler2DRect 	u_tex_unit0;
              uniform float           tex_width,tex_height;
              uniform float 			width,height;
              uniform int 			cell_structure;
              /*
               0 = RECTANGLE,
               1 = SQUARE,
               2 = RHOMBIC,
               3 = HEXAGONAL,
               4 = OBLIQUE
               */
              uniform float 			tile_size;
              uniform float			angle;
              
              
              
              vec2 p1,p2,p3,p4;
              vec2 base1,base2,base3,base4;
              vec2 nextCellSouth, nextCellEast, nextCellNorth, nextCellWest;
              
              /*****************
               * Transformation *
               ******************/
              float map(float val,float inMin,float inMax,float outMin,float outMax){
                  return outMin + ((outMax - outMin) / (inMax - inMin)) * (val - inMin);
              }
              
              float fmod(float val, float modulo){
                  int i = int(val/modulo);
                  return val - (i*modulo);
              }
              
              vec2 translate(vec2 point ,vec2 trans){
                  return point + trans;
              }
              
              vec2 rotate(vec2 point, float angle){
                  mat2 rot = mat2 (
                                   cos(angle), sin(angle),
                                   -sin(angle),cos(angle));
                  return rot * point;
              }
              
              vec2 rotateAt(vec2 point, vec2 anchor, float angle){
                  return vec2(
                              cos(angle)*point.x - sin(angle)*point.y + anchor.x - cos(angle)*anchor.x + sin(angle)*anchor.y,
                              sin(angle)*point.x + cos(angle)*point.y + anchor.y - sin(angle)*anchor.x - cos(angle)*anchor.y);
              }
              
              vec2 reflectAt(vec2 point, vec2 anchor, vec2 dir){
                  vec2 I = point-anchor;
                  vec2 N = normalize(dir);
                  vec2 r = reflect(I,N);
                  return anchor - r;
              }
              
              bool PointInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2)
              {
                  float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
                  float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;
                  
                  if ((s < 0) != (t < 0))
                      return false;
                  
                  float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;
                  if (A < 0.0)
                  {
                      s = -s;
                      t = -t;
                      A = -A;
                  }
                  return s > -0.01 && t > -0.01 && (s + t) < A;
              }
              
              /************************
               * Position calculation *
               ************************/
              
              void updateCornerPoints(){
                  float w = tex_width;
                  float h = tex_height;
                  
                  if (cell_structure == RECTANGLE)
                  {
                      p1 = vec2(0, 0);
                      p2 = vec2(w, 0);
                      p3 = vec2(w, h);
                      p4 = vec2(0, h);
                  }
                  else if (cell_structure == SQUARE)
                  {
                      float length = min(w, h);
                      p1 = vec2((w-length)/2, (h-length)/2);
                      p2 = vec2((w-length)/2 + length, (h-length)/2);
                      p3 = vec2((w-length)/2 + length, (h-length)/2 + length);
                      p4 = vec2((w-length)/2, (h-length)/2 + length);
                  }
                  else if (cell_structure == RHOMBIC)
                  {
                      p1 = vec2(w/2,0);
                      p2 = vec2(w,h/2);
                      p3 = vec2(w/2,h);
                      p4 = vec2(0,h/2);
                  }
                  else if (cell_structure == OBLIQUE)
                  {
                      float length_side = 0.5;
                      float l = w*(1-length_side);
                      p1 = vec2(l,0);
                      p2 = vec2(w,0);
                      p3 = vec2(w-l,h);
                      p4 = vec2(0,h);
                  }
                  else if (cell_structure == HEXAGONAL)
                  {
                      float hmax = w*sqrt(3)/3;
                      float wmax = w;
                      
                      if (hmax>h) {
                          hmax = h;
                          wmax = hmax*3/sqrt(3);
                      }
                      
                      p1 = vec2(wmax*1/3,0);
                      p2 = vec2(wmax,0);
                      p3 = vec2(wmax*2/3,hmax);
                      p4 = vec2(0,hmax);
                      
                      //hack to shrinken the hexagon (to avoid border issues)
                      float scalePix = 1;
                      p1 += vec2(scalePix,scalePix);
                      p2 += vec2(-scalePix,scalePix);
                      p3 += vec2(-scalePix,-scalePix);
                      p4 += vec2(scalePix,-scalePix);
                  }
                  
              }
              
              vec2 do_square(vec2 pos){
                  
                  //startpos
                  float px = pos.x;
                  float py = pos.y;
                  
                  //coord 0,0 to center
                  float dx = (px - width/2);
                  float dy = (py - height/2);
                  
                  //tile coordinate
                  px = fmod(dx,tile_size);
                  py = fmod(dy,tile_size);
                  
                  if (px<0) px = tile_size + px;
                  if (py<0) py = tile_size + py;
                  
                  //map to global texure coordinate
                  px = map(px,0,tile_size,p1.x+1,p3.x-1);
                  py = map(py,0,tile_size,p1.y,p4.y-1);
                  
                  px = fmod(px, p3.x);
                  
                  return vec2(px,py);
              }
              
              vec2 do_hexagonal(vec2 pos){
                  //tile dimensions
                  float tWidth = tile_size;
                  float tHeight = tWidth*p4.y/p3.x;
                  
                  //startpos
                  float px = pos.x;
                  float py = pos.y;
                  
                  //coord 0,0 to center
                  float dx = (px - width/2);
                  //if(dx<0) dx += width;
                  float dy = (py - height/2);//+height;
                  //if(dy<0) dy += height;
                  
                  //dx = px;
                  //dy = py;
                  //number of line of current tile
                  float nlF = dy/tHeight;
                  if (nlF<0) nlF -= 1;
                  int nline = int(nlF);
                  
                  //tile coordinate
                  px = fmod(dx,tWidth);
                  py = fmod(dy,tHeight);
                  
                  if (px<0) px = tWidth + px;
                  if (py<0) py = tHeight + py;
                  
                  //map to global texure coordinate
                  px = map(px,0,tWidth,0,p3.x);
                  py = map(py,0,tHeight,1,p4.y-1);
                  
                  //translation for following lines
                  if(nline>0){
                      px = px + nline*p1.x;
                  }
                  else{ 
                      px = px + 2*p1.x + (p1.x*nline*-1);
                  }
                  
                  px = fmod(px, p3.x);
                  
                  
                  //left upper triangle
                  vec2 a_ = p4 - p1;
                  vec2 b = p4 - vec2(0,py);
                  vec2 b_ = p4;
                  float scale = length(b)/length(b_);
                  vec2 a = a_*scale;
                  vec2 pMax = p4 - a;
                  
                  //more complicated to avoid border issues
                  float pxTemp = px;
                  if (px < pMax.x)
                  {
                      pxTemp = px + p3.x -1;
                  }
                  else if (px < pMax.x+1)
                  {
                      pxTemp = px+1;
                  }
                  
                  px = pxTemp;
                  
                  return vec2(px,py);
              }
              
              void main( void )
              {
                  updateCornerPoints();
                  
                  vec4 color = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
                  vec2 pos = gl_TexCoord[0].st;
                  
                  pos = rotateAt(pos,vec2(width/2,height/2),angle);
                  if(cell_structure == SQUARE){
                      pos = do_square(pos);
                  }
                  if(cell_structure == HEXAGONAL){
                      pos = do_hexagonal(pos);
                  }
                  
                  
                  vec4 c = texture2DRect( u_tex_unit0, pos);
                  gl_FragColor = c;
              }              );
    return out;
}

ofVec2f Ornament::resize(ofVec2f src, ofVec2f dst)
{
    float ratioDst = dst.x/dst.y;
    float ratioSrc = src.x/src.y;
    
    float w = src.x;
    float h = w / ratioDst;
    
    
    if (ratioSrc > ratioDst && h > dst.y)
    {
        h = dst.y;
        w = h*ratioSrc;
    }
    else if (ratioSrc < ratioDst && w > dst.x)
    {
        w = dst.x;
        h = w/ratioSrc;
    }
    return ofVec2f(w, h);
}

void Ornament::getBoundingBox(vector<ofVec2f> input, ofVec2f& pos, ofVec2f& size){
    float xMin = 1000000;
    float xMax = 0;
    float yMin = 1000000;
    float yMax = 0;
    
    for(auto v:input){
        if(v.x < xMin) {xMin = v.x;}
        if(v.x > xMax) {xMax = v.x;}
        if(v.y < yMin) {yMin = v.y;}
        if(v.y > yMax) {yMax = v.y;}
    }
    
    pos = ofVec2f(xMin,yMin);
    size = ofVec2f(xMax-xMin,yMax-yMin);
}

void Ornament::toTextureSpace(ofVec2f& value){
    float ratioSrc = inputTexture.getWidth() / inputTexture.getHeight();
    float ratioDst = width/height;
    value.x = value.x * inputTexture.getWidth() / width;
    value.y = value.y * inputTexture.getHeight() / height;
}


