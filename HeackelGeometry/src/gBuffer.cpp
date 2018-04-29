#include "gBuffer.h"

void GBuffer::setup(int w, int h) {
	ofFbo::Settings s;
	s.width = w;
	s.height = h;
	s.minFilter = GL_NEAREST;
	s.maxFilter = GL_NEAREST;
	s.colorFormats.push_back(GL_RGB); // color
	s.colorFormats.push_back(GL_RGBA32F); // vertex coord
	s.colorFormats.push_back(GL_RGBA32F); // depth + normal
	s.colorFormats.push_back(GL_RGB32F); // HDR map
	s.depthStencilAsTexture = true;
	s.useDepth = true;
	s.useStencil = true;

	fbo.allocate(s);
	
}

void GBuffer::begin(ofCamera &cam) {

	cam.begin();
	cam.end();

	fbo.begin();

	vector<int> bufferInt;
	bufferInt.push_back(TYPE_ALBEDO);
	bufferInt.push_back(TYPE_POSITION);
	bufferInt.push_back(TYPE_DEPTH_NORMAL);
	bufferInt.push_back(TYPE_HDR);
	fbo.setActiveDrawBuffers(bufferInt);

	ofClear(255);
	ofPushView();

	ofRectangle viewPort(0, 0, fbo.getWidth(), fbo.getHeight());
	ofSetOrientation(ofGetOrientation(), cam.isVFlipped());
	ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadMatrix(cam.getProjectionMatrix(viewPort));
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofLoadMatrix(cam.getModelViewMatrix());

	ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());

	ofPushStyle();
	ofEnableDepthTest();
	ofDisableAlphaBlending();

}

void GBuffer::end() {
	ofDisableDepthTest();
	ofPopStyle();

	ofPopView();
	fbo.end();

}