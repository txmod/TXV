/*
 *  Ornament.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Ornament
#define _Ornament

#define STRINGIFY(...) STRINGIFY_AUX(__VA_ARGS__)
#define STRINGIFY_AUX(...) #__VA_ARGS__

#include "ofMain.h"
#include "Tile.h"
#include "TileFactory.h"
#include "OrnamentTypes.h"

// AMENDED BY PAUL - search for PAUL to see changes

class Ornament {
    
public:
    
    Ornament(){};
    
    void setup(int w = 512, int h = 512, WALLPAPER_GROUP wallpaperGroup = WPG_P3, int tileSize = 150, float angle = 0);
    void update();
    void draw(int x, int y); 
    void drawDebug(int x, int y, int w = -1, int h = -1);
    
    void loadTexture(ofTexture texture);
    void setWallpaperGroup(WALLPAPER_GROUP group);
    void setWallpaperGroup(int group);
    WALLPAPER_GROUP getWallpaperGroup();
    int getWallpaperGroupAsInt();
    
    ofTexture& getTexture();
    vector<ofVec2f> getOrnamentBase();
    vector<ofVec2f> getTilePoly();
    
    void setCellStructure(int s);
    int getCellStructure();
    
    void setTileSize(float t);
    int getTileSize();
    
    void setAngle(float angleRad);
    float getAngle();
    
    // ADDED BY PAUL
    void setInputZoomX(float argFloat);
    float getInputZoomX();
    void setInputZoomY(float argFloat);
    float getInputZoomY();
    void setInputShiftX(float argFloat);
    float getInputShiftX();
    void setInputShiftY(float argFloat);
    float getInputShiftY();
    void setInputRotate(float argFloat);
    float getInputRotate();


private:
    void createOrnament();
    
    string getVertexShader();
    string getOrnamentShader();
    string getWallpaperShader();
    
    /// \helper functions
    static ofVec2f resize(ofVec2f src, ofVec2f dst);
    static void getBoundingBox(vector<ofVec2f> input, ofVec2f& pos, ofVec2f& size);
    void toTextureSpace(ofVec2f& value);
    
    ofTexture inputTexture;
    ofTexture outputTexture;
    WALLPAPER_GROUP wallpaperGroup;
    ofFbo fbo;
    ofFbo tileFbo;
    ofFbo resizeFbo;
    
    float tileSize;
    float angle;

    // ADDED BY PAUL
    // with defaults
    float inputZoomX = 1.0;
    float inputZoomY = 1.0;
    float inputShiftX = 0.0;
    float inputShiftY = 0.0;
    float inputRotate = 0.0;
    
    int width,height;
    
    ofShader wallpaperShader;
    ofShader ornamentShader;
    
    std::unique_ptr<Tile> tile;
};

#endif
