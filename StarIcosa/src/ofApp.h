#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "IcosaSurface.hpp"
#include "IcosaStar.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
private:
    ofEasyCam cam;
    
    ofLight light;
    IcosaSurface icosa;
    IcosaStar star;
    ofxPostProcessing post;
};
