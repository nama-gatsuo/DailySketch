#pragma once
#include "ofMain.h"

enum PartMode {
    MULTI_WALL = 0, LATTICE = 1, BLOCKS = 2, SPHERES = 3
};


class PartObj {
public:
    void setup(PartMode mode);
    void update();
    void draw();
    
    bool check();
    
private:
    void createLattice();
    void createWalls();
    void createSphere(ofMatrix4x4 &m, ofFloatColor &c);
    void createBox(ofMatrix4x4 &m, ofFloatColor &c, float w, float h, float d);
    
    ofVboMesh mesh;
    ofNode node;
    
    ofVec3f pos;
    float angle;
    
    float speed;
    float aSpeed;
    int life;
};
