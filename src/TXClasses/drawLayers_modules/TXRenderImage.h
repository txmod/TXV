/*
 *  Copyright 2013 Paul Miller. All rights reserved.

 IMPORTANT NOTE  RE: VIDEO RECORDING - IF RECORDING AUDIO AS WELL, THEN RECORDER WILL ACTUALLY KEEP INSERTING REPEATED FRAMES TO KEEP UP WITH THE AUDIO STREAM EVEN IF YOU'VE PAUSED IT.
 SO, IF RECORDING AUDIO, DON'T USE "NEVER DROP FRAMES"  BECAUSE AUDIO WILL STILL BE OUT OF TIME WITH THE VIDEO, AND DON'T PAUSE THE RECORDING BECAUSE IT WON'T WORK!
*/

#pragma once

#include "ofMain.h"
#include "TXDrawLayersBase.h"
#include "ofxVideoRecorder.h"
#include "ofxImageSequenceRecorder.h"

//#include "TXMain.h"

//    400k
//    800k
//    1 Mbps - Youtube: 360p (SD) 480 x 360  24/25/30 fps
//    1.2 Mbps
//    1.5 Mbps - Youtube: 360p (SD) 480 x 360  48/50/60 fps
//    2 Mbps
//    2.5 Mbps - Youtube: 480p (SD) 858 x 480, 24/25/30 fps
//    3 Mbps
//    4 Mbps - Youtube: 480p (SD) 858 x 480, 48/50/60 fps
//    5 Mbps - Youtube: 720p (Half HD)1280 x 720, 24/25/30 fps
//    6 Mbps
//    7 Mbps - Youtube: 720p (Half HD)1280 x 720, 48/50/60 fps
//    8 Mbps - Youtube: 1080p (Full HD) 1920 x 1080, 24/25/30 fps
//    10 Mbps
//    12 Mbps - Youtube: 1080p (Full HD) 1920 x 1080, 48/50/60 fps
//    14 Mbps
//    16 Mbps - Youtube: 1440p (2k) 2560 x 1440, 24/25/30 fps
//    18 Mbps
//    20 Mbps
//    24 Mbps - Youtube: 1440p (2k) 2560 x 1440 48/50/60 fps
//    30 Mbps
//    35 Mbps
//    40 Mbps - Youtube: 2160p (4k) 3840 x 2160, 24/25/30 fps
//    45 Mbps
//    50 Mbps
//    55 Mbps
//    60 Mbps - Youtube: 2160p (4k) 3840 x 2160, 48/50/60 fps
//    70 Mbps
//    80 Mbps
//    90 Mbps
//    100 Mbps
enum TXVIDEOBITRATE {
    TXVIDEOBITRATE_400K,
    TXVIDEOBITRATE_800K,
    TXVIDEOBITRATE_1000K,
    TXVIDEOBITRATE_1200K,
    TXVIDEOBITRATE_1500K,
    TXVIDEOBITRATE_2000K,
    TXVIDEOBITRATE_2500K,
    TXVIDEOBITRATE_3000K,
    TXVIDEOBITRATE_4000K,
    TXVIDEOBITRATE_5000K,
    TXVIDEOBITRATE_6000K,
    TXVIDEOBITRATE_7000K,
    TXVIDEOBITRATE_8000K,
    TXVIDEOBITRATE_10000K,
    TXVIDEOBITRATE_12000K,
    TXVIDEOBITRATE_14000K,
    TXVIDEOBITRATE_16000K,
    TXVIDEOBITRATE_18000K,
    TXVIDEOBITRATE_20000K,
    TXVIDEOBITRATE_25000K,
    TXVIDEOBITRATE_30000K,
    TXVIDEOBITRATE_35000K,
    TXVIDEOBITRATE_40000K,
    TXVIDEOBITRATE_45000K,
    TXVIDEOBITRATE_50000K,
    TXVIDEOBITRATE_55000K,
    TXVIDEOBITRATE_60000K,
    TXVIDEOBITRATE_70000K,
    TXVIDEOBITRATE_80000K,
    TXVIDEOBITRATE_90000K,
    TXVIDEOBITRATE_100000K,
    TXVIDEOBITRATE_TOTAL
};

/* AUDIO REMOVED FOR NOW
enum TXAUDIOBITRATE {
    TXAUDIOBITRATE_128K,
    TXAUDIOBITRATE_160K,
    TXAUDIOBITRATE_192K,
    TXAUDIOBITRATE_256K,
    TXAUDIOBITRATE_320K,
    TXAUDIOBITRATE_TOTAL
};
 */

enum TXVIDRECCODEC {
    TXVIDRECCODEC_MPEG4,
    TXVIDRECCODEC_PRORES_LT,
    TXVIDRECCODEC_PRORES_STANDARD,
    TXVIDRECCODEC_PRORES_HQ,
    TXVIDRECCODEC_PRORES_4444,
    TXVIDRECCODEC_PRORES_4444XQ,
    TXVIDRECCODEC_RAWVIDEO,
    TXVIDRECCODEC_H264,
    TXVIDRECCODEC_H264_CRF,
    TXVIDRECCODEC_H265,
    TXVIDRECCODEC_H265_CRF,
    TXVIDRECCODEC_TOTAL
};

enum TXVIDREC_H2645SPEEDPRESET {
    TXVIDREC_H2645SPEEDPRESET_VERYSLOW, //best quality
    TXVIDREC_H2645SPEEDPRESET_SLOWER,
    TXVIDREC_H2645SPEEDPRESET_SLOW,
    TXVIDREC_H2645SPEEDPRESET_MEDIUM,  // default
    TXVIDREC_H2645SPEEDPRESET_FAST,
    TXVIDREC_H2645SPEEDPRESET_FASTER,
    TXVIDREC_H2645SPEEDPRESET_VERYFAST, // worst quality
    TXVIDREC_H2645SPEEDPRESET_TOTAL,
};

// REMOVED FOR NOW - USE MOV
//enum TXVIDREC_FILEEXT {
//    TXVIDREC_FILEEXT_MOV,
//    TXVIDREC_FILEEXT_MP4,
//    TXVIDREC_FILEEXT_AVI,
//    TXVIDREC_FILEEXT_TOTAL
//};

class TXRenderImage  :  public TXDrawLayersBase
{
public:
	// constructor
	TXRenderImage();
    
    // destructor
    ~TXRenderImage();

	void setup();
	void update();
	void draw();
	void allocateTexture();
    void clearTexture();
	void renderTexture(bool clearFirstArg);
    void windowResized(int w, int h);
    int getTextureWidth(); // overide base class
    int getTextureHeight(); // overide base class
    ofTexture *  getTexture(); // overide base class
    ofPixelsRef getPixels(); // overide base class
    
    void setupVideoRecording();
    void startVideoRecording();
    void stopVideoRecording();
    string getImageFormatString(int intArg);
    void saveImage();
    void setupImageSequenceRecorder();
    void startImageSeqRecording();
    void stopImageSeqRecording();


    void recordVideoChanged(ofAbstractParameter & parameterArg );
    void renderSizeChanged(int & intArg);
    void imageSeqSettingsChanged(string & stringArg);
    void imageSeqFormatChanged(int & intArg);
    void recordImageSeqChanged(ofAbstractParameter & parameterArg );
    
    int getRenderWidth();
    int getRenderHeight();

    // parameters
    
    // render parameters
    ofPtr<TXModParamInt> drawLayersRule;
    ofPtr<TXModParamBool> renderContinuosly; // bool
    ofPtr<TXModParamBool> renderNow; // bool
    ofParameter<int> renderWidthHeightRule;
    ofParameter<int> renderCustomWidth;
    ofParameter<int> renderCustomHeight;
    ofPtr<TXModParamBool> clearBeforeRender; // bool
    ofPtr<TXModParamBool> clearNow; // bool
    ofPtr<TXModParamFloat> clearColorHue;
    ofPtr<TXModParamFloat> clearColorSaturation;
    ofPtr<TXModParamFloat> clearColorBrightness;
    ofPtr<TXModParamFloat> clearColorAlpha;
    ofParameter<bool>  clearColorHSBAsRGB;
    
    // draw parameters
    ofPtr<TXModParamFloat> alpha;
    ofPtr<TXModParamFloat> drawPosX;
    ofPtr<TXModParamFloat> drawPosY;
    ofPtr<TXModParamFloat> drawWidth;
    ofPtr<TXModParamFloat> drawHeight;
    ofPtr<TXModParamFloat> anchorX;
    ofPtr<TXModParamFloat> anchorY;
    ofPtr<TXModParamFloat> rotate;
    ofPtr<TXModParamFloat> rotateMultiply;
    ofPtr<TXModParamFloat> scaleX;
    ofPtr<TXModParamFloat> scaleY;
    ofParameter<bool> useScaleXForScaleY;
    
    // video record parameters
    ofPtr<TXModParamBool> recordVideo;
    ofPtr<TXModParamBool> pauseRecordVideo;
    ofParameter<float> maxVideoRecordTimeMinutes;
    ofParameter<string> recordVideoFolder;
    ofParameter<string> recordVideoFileNamePrefix;
    ofParameter<int> recordVideoCodec;
    ofParameter<int> recordVideoFileType;
    ofParameter<int> recordVideoBitrate;
    ofParameter<int> recordVideoConstantRateFactor;
    ofParameter<int> recordVideoH6245SpeedPreset;
/* AUDIO REMOVED FOR NOW
    // audio record parameters
    ofParameter<bool> recordAudioWithVideo;
    ofParameter<int> recordAudioDeviceID;
    ofParameter<int> recordAudioBitrate;
 */
    
    // save image parameters
    ofPtr<TXModParamBool> saveImageNow;
    ofParameter<string> saveImageFolder;
    ofParameter<string> saveImageFileNamePrefix;
    ofParameter<int> saveImageFormat;    //"0 - jpg is just right", "1 - png is really slow but high res", "2 - bmp is fast but big",

    // image sequence record parameters
    ofPtr<TXModParamBool> recordImageSeq;
    ofPtr<TXModParamBool> pauseRecordImageSeq;
    ofParameter<float> maxImageSeqRecordTimeMinutes;
    ofParameter<string> imageSeqFolder;
    ofParameter<string> imageSeqFileNamePrefix;
    ofParameter<int> imageSeqFormat;    //"0 - jpg is just right", "1 - png is really slow but high res", "2 - bmp is fast but big",

    ofFbo outImage;

private:
    ofPixels pix;
    ofPixels recordPix;
    ofMesh drawMesh;
	ofShader drawShader;
    bool oldRenderNow;
    bool oldClearNow;
    
    ofxVideoRecorder vidRecorder;
    ofxImageSequenceRecorder imageSeqRecorder;
    // ofSoundStream    soundStream;  // AUDIO REMOVED FOR NOW
    bool isRecordingVideo;
    unsigned int numRecordedVideoFrames;
    bool oldSaveImageNow;
    const static int audioSampleRate = 44100;
    const static int audioChannels = 2;
    
    bool imageSeqRecorderSetupRequired;
    unsigned int numRecordedImageSeqFrames;
    bool isRecordingImageSeq;
};

