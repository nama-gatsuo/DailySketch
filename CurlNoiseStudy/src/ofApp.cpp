#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofDisableBlendMode();
    
    emitter.setup();
    emitter.setPosition(ofVec3f(0));
    
    panel.setup();
    panel.add(radius.set("radius", 100, 10, 1000));
    panel.add(turbulence.set("turbulence", 0.1, 0., 1.0));
    panel.add(noiseScale.set("noise scale", 0.1, 0.1, 100.));
    panel.add(noiseStrength.set("noise strength", 0.1, 0.1, 100.));
    panel.add(pointSize.set("point size", 1., 0.1, 10.0));
    panel.add(fromColor.set("1st color", ofFloatColor(1.), ofFloatColor(0.,0.), ofFloatColor(1.)));
    panel.add(toColor.set("2nd color", ofFloatColor(1.), ofFloatColor(0.,0.), ofFloatColor(1.)));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    emitter.update();
    
    if (isShowPanel) {
        emitter.setRadius(radius.get());
        emitter.setNoiseScale(noiseScale.get());
        emitter.setNoiseStrength(noiseStrength.get());
        emitter.setRadius(radius.get());
        emitter.setToColor(toColor.get());
        emitter.setFromColor(fromColor.get());
        emitter.setTurbulence(turbulence.get());
        emitter.setPointSize(pointSize.get());
        emitter.createStartPos();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    emitter.draw();
    cam.end();
    
//    emitter.debugDraw();
    
    if (isShowPanel) panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


