#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class BaseObject {
public:
	BaseObject() {}

	virtual void setup() = 0;
	virtual void update(float dt) = 0;
	virtual void draw(float linearDepthScalar=0, bool isShadow=false) = 0;
	virtual void bang(int note, int velocity) = 0;

	virtual void drawGui() = 0;

protected:
	void addBox(const glm::mat4& modelMatrix, const ofFloatColor& col) {
		ofMesh box = ofMesh::box(1.f, 1.f, 1.f, 1, 1, 1);
		glm::mat4 normalMatrix = glm::inverse(glm::transpose(modelMatrix));

		for (int i = 0; i < box.getNumVertices(); i++) {
			box.setVertex(i, modelMatrix * glm::vec4(box.getVertex(i), 1.f));
			box.setNormal(i, normalMatrix * glm::vec4(box.getNormal(i), 0.f));
		}
		box.addColors(vector<ofFloatColor>(box.getNumVertices(), col));

		mesh.append(box);
	}
	ofShader shader;
	ofVboMesh mesh;
	ofxPanel panel;
};
