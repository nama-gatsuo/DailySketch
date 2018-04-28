#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	ofSetFrameRate(60);

	deferred.init(ofGetWidth(), ofGetHeight());
	params.setup(deferred);

	object = make_shared<MyObject>();
	object->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	object->update(0.1f);
}

//--------------------------------------------------------------
void ofApp::draw(){
	params.getShadow()->beginShadowMap();
	object->draw();
	params.getPointLight()->drawLights();
	params.getShadow()->endShadowMap();

	deferred.begin(cam);
	object->draw();
	params.getPointLight()->drawLights();
	deferred.end();

	if (!isShowPanel) {
		params.drawGui();
		object->drawGui();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') isShowPanel = !isShowPanel;
}
