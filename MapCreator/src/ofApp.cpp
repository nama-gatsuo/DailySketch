#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    mc.setup();
    mc.setLayer();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    mc.draw(0,0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        ofImage img;
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save("screenshot.png");
    }
    
}


