#pragma once

#include "ofMain.h"
#include "MeshEarth.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    ofEasyCam cam;
    MeshEarth me;
};
