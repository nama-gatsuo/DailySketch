#pragma once
#include "BaseObject.h"

class MyObject : public BaseObject {
public:
	void setup() override {

		panel.setName("MyObject");
		addBox(glm::scale(glm::vec3(100.f)), ofFloatColor(1.f));
		
	}
	void update(float dt) override {
	
	}
	void draw() override {
		mesh.draw();
	}
	void bang(int note, int velocity) override {
	
	}

	void drawGui() override {
		panel.draw();
	}
};
