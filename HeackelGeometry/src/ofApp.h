#pragma once

#include "ofMain.h"
#include "GenGeom.h"
#include "gBuffer.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam cam;
	GenGeom gg;
	GBuffer gbuffer;
	ofFbo pingPong[2];
	unsigned currentReadFbo;
	ofShader edgeShader;
};
