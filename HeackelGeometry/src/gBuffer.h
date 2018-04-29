#pragma once
#include "ofMain.h"
class GBuffer {
private:
	ofFbo fbo;
	
public:
	enum BufferType {
		TYPE_ALBEDO = 0, TYPE_POSITION = 1, TYPE_DEPTH_NORMAL = 2, TYPE_HDR = 3
	};
	GBuffer() {}
	void setup(int w = ofGetWidth(), int h = ofGetHeight());
	void begin(ofCamera& cam);
	void end();
	
	ofTexture& getTexture(int index) {
		return fbo.getTexture(index);
	}
	ofFbo& getFbo() {
		return fbo;
	}
};