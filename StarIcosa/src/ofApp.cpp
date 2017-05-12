#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofEnableDepthTest();
    
    light.setAmbientColor(ofFloatColor(0.1));
    light.setDiffuseColor(ofFloatColor(0.61,0.7,0.6));
    light.setSpecularColor(ofFloatColor(0.94,1.0,0.91));
    light.setDirectional();
    light.setPosition(1, 1, 1);
    light.lookAt(ofVec3f(0,0,0));
    
    icosa.setup();
    star.setup();
    
    post.init();
    
    post.createPass<SSAOPass>();
    post.createPass<BloomPass>();
    post.createPass<DofPass>();
    post.createPass<GodRaysPass>();
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    post.begin(cam);
    light.enable();
    
    star.draw();
    icosa.draw();
    light.disable();
    
    post.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

