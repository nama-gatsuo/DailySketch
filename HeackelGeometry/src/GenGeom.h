#pragma once
#include "ofMain.h"

class GenGeom {
public:
	GenGeom() {}
	void setup() {
		mesh = ofMesh::icosphere(200, 2);

		shader.load("shader/genGeom.vert", "shader/genGeom.frag", "shader/genGeom.geom");
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		shader.setGeometryInputType(GL_TRIANGLES);
		shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
		shader.setGeometryOutputCount(81);
		
	}
	void update() {}
	void draw(ofCamera& cam) {
		shader.begin();
		shader.setUniform1f("farClip", cam.getFarClip());
		shader.setUniform1f("nearClip", cam.getNearClip());
		shader.setUniform1f("f1", - 100 * sin(ofGetElapsedTimef()*0.2));
		shader.setUniform1f("f2", 80 * sin(ofGetElapsedTimef()*0.3 + HALF_PI));
		shader.setUniform1f("f3", 60 * sin(ofGetElapsedTimef()*0.25+PI));
		shader.setUniform1f("wireWidth", 0.1 + 0.08 * sin(ofGetElapsedTimef()*0.4 + PI));
		mesh.draw();
		shader.end();
	}
private:
	
	ofVboMesh mesh;
	ofShader shader;

};