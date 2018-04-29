#pragma once

#include "ofMain.h"
#include "ofxDeferredShading.h"
#include "ofxDeferredParams.h"
#include "GridMountain.h"
#include "CurlTrail.h"

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

	vector<shared_ptr<BaseObject>> objects;

};
