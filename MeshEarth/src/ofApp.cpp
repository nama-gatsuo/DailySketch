#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    
    me.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    me.draw();
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

