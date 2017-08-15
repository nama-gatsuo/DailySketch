#pragma once

#include "ofMain.h"
#include "MapCreator.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    MapCreator mc;
};
