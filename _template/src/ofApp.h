#pragma once

#include "ofMain.h"
#include "ofxDeferredShading.h"
#include "ofxDeferredParams.h"
#include "MyObject.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofxDeferredProcessing deferred;
	ofxDeferredParams params;
	ofEasyCam cam;
	bool isShowPanel = false;

	shared_ptr<BaseObject> object;

};
