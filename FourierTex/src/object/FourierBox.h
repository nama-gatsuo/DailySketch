#pragma once
#include "BaseObject.h"

class FourierBox : public BaseObject {
public:
	void setup() override {
		panel.setup("MyObject");
		panel.add(h.set("vert hieght", 20, 500, 800));
		for (int i = 0; i < 2; i++) {
			fp[i].group.setName("fourier"+ofToString(i));
			fp[i].num.set("num", 6, 3, 16);
			fp[i].radius.set("radius", 0.5, 0.1, 2.);
			fp[i].freq.set("frequency", 6, 3, 24);
			fp[i].power.set("power", 0.125, 0.0, 0.5);

			fp[i].group.add(fp[i].num);
			fp[i].group.add(fp[i].radius);
			fp[i].group.add(fp[i].freq);
			fp[i].group.add(fp[i].power);

			panel.add(fp[i].group);
		}

		tex.allocate(512, 512, GL_R16);

		mesh = ofMesh::box(800, 800, 800, 63, 63, 63);
		
		boxShader.load("shader/scene/boxShader");
		texShader.load("shader/scene/texShader");
		
	}
	void update(float dt) override {

		int ns[2]{ fp[0].num.get(), fp[1].num.get() };
		float rs[2]{ fp[0].radius.get(), fp[1].radius.get() };
		int fs[2]{ fp[0].freq.get(), fp[1].freq.get() };
		float ps[2]{ fp[0].power.get(), fp[1].power.get() };

		tex.begin();
		ofClear(0);

		texShader.begin();
		texShader.setUniform1iv("ns", ns, 2);
		texShader.setUniform1fv("rs", rs, 2);
		texShader.setUniform1iv("fs", fs, 2);
		texShader.setUniform1fv("ps", ps, 2);
		texShader.setUniform1f("time", ofGetElapsedTimef());

		tex.draw(0, 0);
		texShader.end();
		tex.end();

	}
	void draw(float linearDepthScalar, bool isShadow) override {
		
		boxShader.begin();
		boxShader.setUniform1f("linearDepthScalar", linearDepthScalar);
		boxShader.setUniformTexture("fourierTex", tex.getTexture(), 5);
		boxShader.setUniform1f("hFactor", h.get());
		mesh.draw();
		boxShader.end();
	}
	void bang(int note, int velocity) override {

	}

	void drawGui() override {
		tex.draw(0, 0, 256, 256);
		panel.draw();
	}

private:
	ofFbo tex;
	ofShader texShader;
	ofShader boxShader;

	struct FParam {
		ofParameterGroup group;
		ofParameter<int> num;
		ofParameter<float> radius;
		ofParameter<float> power;
		ofParameter<int> freq;
	} fp[2];
	
	ofParameter<float> h;

};
