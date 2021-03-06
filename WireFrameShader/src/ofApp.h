#pragma once

#include "ofMain.h"
#include "ofxDeferredShading.h"
#include "ofxGui.h"
#include "WireFrameShader.hpp"
#include "MassOcta.hpp"

using namespace ofxDeferredShading;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void setupDeferred();
    void updateDeferredParam();

private:
    ofVboMesh sphere;
    ofVboMesh plane;
    MassOcta octa;
    ofParameter<float> wireWidth;
    ofxToggle bDrawFace;
    
    WireFrameShader shader;
    ofEasyCam cam;
    
    ofxDeferredProcessing deferred;
    PointLightPass* lightingPass;
    SsaoPass* ssaoPass;
    ShadowLightPass* shadowLightPass;
    DofPass* dofPass;
    
    // gui
    bool isShow = true;
    ofxPanel panel;
    ofParameterGroup pl1;
    ofParameter<ofVec3f> pl1_pos;
    ofParameter<ofFloatColor> pl1_diff;
    ofParameter<ofFloatColor> pl1_spe;
    ofParameter<float> pl1_int;
    ofParameter<float> pl1_rad;
    
    ofParameterGroup pl2;
    ofParameter<ofVec3f> pl2_pos;
    ofParameter<ofFloatColor> pl2_diff;
    ofParameter<ofFloatColor> pl2_spe;
    ofParameter<float> pl2_int;
    ofParameter<float> pl2_rad;
    
    ofParameterGroup ao;
    ofParameter<float> ao_rad;
    ofParameter<float> ao_dark;
    
    ofParameterGroup shadow;
    ofParameter<float> sha_amb;
    ofParameter<float> sha_dif;
    ofParameter<float> sha_dark;
    ofParameter<float> sha_blend;
    
    ofParameterGroup dof;
    ofParameter<float> dof_blur;
    ofParameter<float> dof_ape;
    ofParameter<float> dof_focal;
};
