#pragma once
#include "BaseObject.h"

class GridMountain : public BaseObject {
public:
	void setup() override {
		panel.setup();
		panel.setName("GridMountain");

		time = 0.f;

		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		for (size_t z = 0; z < 200; z++) {
			for (size_t x = 0; x < 60; x++) {
				float px1 = 20.f * (x - 60. / 2.);
				float pz1 = 20.f * (z - 200. / 2.);
				float px2 = 20.f * (x + 1 - 60. / 2.);
				float pz2 = 20.f * (z + 1 - 200. / 2.);
				float y = -100.f;

				mesh.addVertex(ofVec3f(px1, y, pz1));
				mesh.addTexCoord(ofVec2f(x, z));
				mesh.addVertex(ofVec3f(px2, y, pz1));
				mesh.addTexCoord(ofVec2f(x + 1, z));
				mesh.addVertex(ofVec3f(px1, y, pz2));
				mesh.addTexCoord(ofVec2f(x, z + 1));

				mesh.addVertex(ofVec3f(px2, y, pz1));
				mesh.addTexCoord(ofVec2f(x + 1, z));
				mesh.addVertex(ofVec3f(px2, y, pz2));
				mesh.addTexCoord(ofVec2f(x + 1, z + 1));
				mesh.addVertex(ofVec3f(px1, y, pz2));
				mesh.addTexCoord(ofVec2f(x, z + 1));
			}
		}

		shader.load("shader/scene/GridMountain.vert", "shader/scene/GridMountain.frag", "shader/scene/GridMountain.geom");
		shader.setGeometryInputType(GL_TRIANGLES);
		shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
		shader.setGeometryOutputCount(3);

	}
	void update(float dt) override {
		time += dt;
	}
	void draw(float linearDepthScalar, bool isShadow) override {
		shader.begin();
		shader.setUniform1f("time", time * 0.2f);
		shader.setUniform1f("linearDepthScalar", linearDepthScalar);
		shader.setUniform1i("shadowFlag", isShadow?1:0);
		mesh.draw();
		shader.end();
	}
	void bang(int note, int velocity) override {
	
	}

	void drawGui() override {
		panel.draw();
	}

private:
	float time;
};
