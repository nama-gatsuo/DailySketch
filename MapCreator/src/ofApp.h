#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "MapCreator.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    MapCreator mc;
    ofxTrueTypeFontUC font;
    
    int mode = 0;
    string modeName[4] = {
        "GDP Per Capita", "Population Growth Rate", "Death Rate", "Suicide Rate"
    };
    int year;
    int ys = 0;
};
