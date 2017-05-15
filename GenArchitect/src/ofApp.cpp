#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofBackground(64);
    
    light.setAmbientColor(ofFloatColor(0.1));
    light.setDiffuseColor(ofFloatColor(0.6));
    light.setSpecularColor(ofFloatColor(0.94,1.0,0.91));
    light.setDirectional();
    light.setPosition(1, 1, 1);
    light.lookAt(ofVec3f(0,0,0));
    
    post.init();
    post.createPass<SSAOPass>();
    post.createPass<DofPass>();
    post.createPass<GodRaysPass>();
    archi.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    post.begin(cam);
    light.enable();
    
    archi.draw();
    
    light.disable();
    post.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

