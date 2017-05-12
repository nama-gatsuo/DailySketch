#pragma once

#include "ofMain.h"
#include "FractalIcosa.hpp"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofEasyCam cam;
    ofLight light;
    FractalIcosa icosa;
    ofxPostProcessing post;
};
