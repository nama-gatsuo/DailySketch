#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableDepthTest();
    ofBackground(128);
    
    light.setAmbientColor(ofFloatColor(0.3));
    light.setDiffuseColor(ofFloatColor(0.7));
    light.setSpecularColor(ofFloatColor(0.98,1.0,0.97));
    light.setDirectional();
    light.setPosition(1, 1, 1);
    light.lookAt(ofVec3f(0,0,0));
    
    icosa.setup();
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<SSAOPass>();
    post.createPass<DofPass>();
    post.createPass<GodRaysPass>();
    
    cam.setNearClip(0.001);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    post.begin(cam);
//    cam.begin();
    light.enable();
    icosa.draw();
    light.disable();
//    cam.end();
    post.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

