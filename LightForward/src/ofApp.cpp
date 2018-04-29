#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	ofSetFrameRate(60);

	deferred.init(ofGetWidth(), ofGetHeight());
	params.setup(deferred);

	objects.push_back(make_shared<GridMountain>());
	objects.push_back(make_shared<CurlTrail>());
	
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->setup();
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update(0.1f);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofxDeferred::ShadowLightPass* tmpShadow = params.getShadow().get();
	float linearDepthScalar = tmpShadow->getLinearScalar();

	// need normalmatrix , linearDepthScalar

	tmpShadow->beginShadowMap();
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw(linearDepthScalar, true);
	}
	params.getPointLight()->drawLights();
	tmpShadow->endShadowMap();

	linearDepthScalar = 1. / (cam.getFarClip() - cam.getNearClip());

	deferred.begin(cam, true);
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw(linearDepthScalar);
	}
	params.getPointLight()->drawLights(cam);
	deferred.end();

	if (!isShowPanel) {
		ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), ofGetWidth() / 2, ofGetHeight() - 12);
		params.drawGui();
		for (size_t i = 0; i < objects.size(); i++) {
			objects[i]->drawGui();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') isShowPanel = !isShowPanel;
}
