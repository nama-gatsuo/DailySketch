#pragma once

#include "ofMain.h"
#include "GenArchitecture.hpp"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:
    ofEasyCam cam;
    ofLight light;
    ofxPostProcessing post;
    GenArchitecture archi;
};
