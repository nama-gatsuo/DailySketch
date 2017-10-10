#pragma once

#include "ofMain.h"
#include "ParticleEmitter.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
private:
    ofEasyCam cam;
    ParticleEmitter emitter;
    
    ofxPanel panel;
    bool isShowPanel = true;
    ofParameter<float> radius;
    ofParameter<float> noiseScale;
    ofParameter<float> noiseStrength;
    ofParameter<float> pointSize;
    ofParameter<float> turbulence;
    ofParameter<ofFloatColor> fromColor;
    ofParameter<ofFloatColor> toColor;
    ofParameter<ofVec3f> pos;
    
};
