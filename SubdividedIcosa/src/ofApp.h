#pragma once

#include "ofMain.h"
#include "IcosaGeom.hpp"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofEasyCam cam;
    ofLight light;
    IcosaGeom icosa;
    
    ofxPostProcessing post;
};
