#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gg.setup();
	gbuffer.setup(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < 2; i++) {
		pingPong[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	}
	
	currentReadFbo = 0;
	edgeShader.load("shader/passThru.vert", "shader/edge.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gbuffer.begin(cam);
	gg.draw(cam);
	gbuffer.end();

	ofPushStyle();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	ofSetColor(255, 255, 255);

	pingPong[0].begin();
	ofClear(0.);
	edgeShader.begin();
	edgeShader.setUniformTexture("colorTex", gbuffer.getTexture(GBuffer::TYPE_ALBEDO), 1);
	edgeShader.setUniformTexture("positionTex", gbuffer.getTexture(GBuffer::TYPE_POSITION), 2);
	edgeShader.setUniformTexture("normalAndDepthTex", gbuffer.getTexture(GBuffer::TYPE_DEPTH_NORMAL), 3);

	pingPong[1].draw(0,0);
	edgeShader.end();
	pingPong[0].end();
	
	pingPong[0].draw(0,0);
	//gbuffer.getTexture(GBuffer::TYPE_DEPTH_NORMAL).draw(0,0);
	glPopAttrib();
	ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
