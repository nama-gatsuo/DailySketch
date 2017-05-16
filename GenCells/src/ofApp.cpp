#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofBackground(64);
    
    light.setAmbientColor(ofFloatColor(0.4));
    light.setDiffuseColor(ofFloatColor(0.7));
    light.setSpecularColor(ofFloatColor(0.94,1.0,0.91));
    light.setDirectional();
    light.setPosition(1, 1, 1);
    light.lookAt(ofVec3f(0,0,0));
    
    post.init();
    post.createPass<SSAOPass>();
//    post.createPass<DofPass>();
    post.createPass<GodRaysPass>();
    post.createPass<BloomPass>();
    cells.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    post.begin(cam);
    light.enable();
    
    cells.draw();
    
    light.disable();
    post.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

