#pragma once

#include "ofMain.h"
#include "GenCells.hpp"
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
    GenCells cells;
};
