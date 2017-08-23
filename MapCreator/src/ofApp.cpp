#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    mc.setup();
    
    font.load("font/OpenSans-Light.ttf", 32);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    mc.draw(0,0, ofGetWidth(), ofGetHeight());
    font.drawString(modeName[mode] + ", " + ofToString(year), 20,ofGetHeight() - 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        ofImage img;
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save(modeName[mode] + ", " + ofToString(year) + ".png");
    } else if (key == 'a') {
        year = 2015;
        mc.setLayerA();
        mode = 0;
    } else if (key == 's') {
        year = 1960;
        mc.setLayerB(year);
        mode = 1;
    } else if (key == 'd') {
        year = 1960;
        mc.setLayerC(year);
        mode = 2;
    } else if (key == 'f') {
        year = 2000;
        ys = 0;
        mc.setLayerD(ys);
        mode = 3;
    } else if (key == 'g') {
        year = 0;
        mc.setLayerE();
        mode = 4;
    }
    else if (key == OF_KEY_UP) {
        if (mode == 1) {
            if (year < 2016) {
                year++;
                mc.setLayerB(year);
            }
        } else if (mode == 2) {
            if (year < 2015) {
                year++;
                mc.setLayerC(year);
            }
        } else if (mode == 3) {
            if (ys < 3) {
                ys++;
                year += 5;
                mc.setLayerD(ys);
            }
        
        }
        
    }
    else if (key == OF_KEY_DOWN) {
        if (mode == 1) {
            if (year > 1960) {
                year--;
                mc.setLayerB(year);
            }
        } if (mode == 2) {
            if (year > 1960) {
                year--;
                mc.setLayerC(year);
            }
        } else if (mode == 3) {
            if (ys > 0) {
                ys--;
                year -= 5;
                mc.setLayerD(ys);
            }
            
        }
        
    }
}


