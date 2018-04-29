#pragma once
#include "ofMain.h"
#include "BaseObject.h"
#include "PingPongBuffer.h"

#define SPEED 80.f

using namespace glm;

class CurlTrail : public BaseObject {
public:
	
	void setup() override {

		panel.setup();
		panel.setName("CurlTrail");

		shader.load("shader/scene/noiseRender.vert", "shader/scene/sprite.frag");
		updateShader.load("shader/scene/passThru.vert", "shader/scene/noiseUpdate.frag");

		int w = 256, h = 256;
		for (size_t i = 0; i < w; i++) {
			for (size_t j = 0; j < h; j++) {
				mesh.addVertex(vec3(ofRandom(-1., 1.), ofRandom(-1., 1.), ofRandom(-1., 1.)));
				mesh.addTexCoord(vec2(i, j));
			}
		}
		mesh.setMode(OF_PRIMITIVE_POINTS);

		pp.allocate(w, h);
		creatFlag = true;

	};
	void update(float dt) override {

		ofDisableAlphaBlending();
		pp.dst->begin();
		pp.dst->activateAllDrawBuffers();
		
		ofVec3f prev = getCurvePoint(time);
		time += dt * 0.5f;
		emitPos = getCurvePoint(time);

		ofClear(0, 0);
		updateShader.begin();
		updateShader.setUniform3f("emitPos", emitPos);
		updateShader.setUniform3f("prevPos", prev);
		updateShader.setUniform1f("dt", dt*0.5f);
		updateShader.setUniform1f("speed", SPEED);
		updateShader.setUniform1f("noiseStrength", 2.1 + 1. * (sin(time * 0.2) + 1.));
		updateShader.setUniformTexture("posAndLifeTex", pp.src->getTexture(0), 1);
		updateShader.setUniformTexture("velTex", pp.src->getTexture(1), 2);
		updateShader.setUniform1i("createFlag", creatFlag ? 1 : 0);

		pp.src->draw(0, 0);

		updateShader.end();
		pp.dst->end();
		ofEnableAlphaBlending();

		pp.swap();
		creatFlag = false;

	};
	void draw(float linearDepthScalar, bool isShadow) override {

		if (isShadow) return;

		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glDepthMask(false);

		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		//ofDisableDepthTest();

		shader.begin();
		shader.setUniformTexture("posAndLifeTex", pp.dst->getTexture(0), 0);
		shader.setUniform1f("linearDepthScalar", linearDepthScalar);
		shader.setUniform1f("time", time);
		mesh.draw();
		shader.end();

		//ofEnableDepthTest();
		glDepthMask(true);
		ofDisableBlendMode();

	};

	void bang(int note, int velocity) override {

	}

	void drawGui() override {
		panel.draw();
	}

private:
	vec3 getCurvePoint(float t) {
		vec3 freq1(0.2, -0.1, 0.31);
		vec3 freq2(-0.103, 0.2, -0.29);
		t *= 4.f;
		vec3 v = vec3(
			sin(freq1.x * t + (1 + sin(freq2.x * t) * 0.5)) * 0.6,
			sin(freq1.y * t + (1 + sin(freq2.y * t) * 0.5)) * 0.3 + 0.1,
			sin(freq1.z * t + (1 + sin(freq2.z * t) * 0.5)) - 2.f
		) * 200.f;
		
		return v;
	};
	
	PingPongBuffer pp;
	ofShader updateShader;
	ofVec3f emitPos;
	ofVec3f dir;
	bool creatFlag;
	float noiseScale, turbulance;
	float time;

};