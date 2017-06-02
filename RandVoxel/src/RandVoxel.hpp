#pragma once
#include "ofMain.h"


class RandVoxel {
public:
    RandVoxel(){};
    void setup(){
        
        for (int i = 0; i < 100; i++) {
            
            ofPoint p(ofRandom(-600, 600), ofRandom(-800, 800), ofRandom(-600, 600));
            createRoom(ofRandom(100, 200), ofRandom(100, 200), p);
        
        }
        
    };
    void draw(){
        mesh.draw(OF_MESH_FILL);
    }
private:
    
    void createRoom(float w, float h, ofPoint pos) {
        
        ofMatrix4x4 mat;
        
        for (int i = 0; i < 4; i++) {
            
            mat.makeIdentityMatrix();
            mat.glTranslate(pos.x, pos.y, pos.z);
            mat.glRotate(90*i, 0, 1, 0);
            mat.glTranslate(w/2, 0, 0);
            mat.glRotate(-90, 0, 0, 1);
            createWall(mat, w, h);
            
        }
        
        mat.makeIdentityMatrix();
        mat.glTranslate(pos.x, pos.y+h/2, pos.z);
        createWall(mat, w, w);
    }
    
    void createWall(ofMatrix4x4 m, float w, float d){
        
        int num = ceil(w * d / 20000);
        ofFloatColor c(1.0);
        c.setHsb(0.33, 1.0, 0.1);
        
        for (int i = 0; i < num; i++) {
            ofMatrix4x4 mat = m;
            mat.glTranslate(ofRandom(-w/3, w/3), 0.0, ofRandom(-d/3, d/3));
            mat.glScale(ofRandom(w*0.4, w*0.6), 1.0, ofRandom(d*0.4, d*0.6));
            addBox(mat, c);
        }
        
        for (int i = 0; i < num; i++) {
            ofMatrix4x4 mat = m;
            mat.glTranslate(ofRandom(-w/2, w/2), 10.0, ofRandom(-d/2, d/2));
            mat.glScale(ofRandom(w/4, w), 5.0, 5.0);
            addBox(mat, ofFloatColor(0.71, 1.3, 1.0));
        }
        
        for (int i = 0; i < num; i++) {
            ofMatrix4x4 mat = m;
            mat.glTranslate(ofRandom(-w/2, w/2), 10.0, ofRandom(-d/2, d/2));
            mat.glScale(5.0, 5.0, ofRandom(d/4, d));
            addBox(mat, ofFloatColor(0.71, 1.3, 1.0));
        }

    }
    
    void addBox(const ofMatrix4x4& mat, ofFloatColor c){
        
        ofMesh box = ofMesh::box(1.0, 1.0, 1.0, 1,1,1);
        for (int i = 0; i < box.getNumVertices(); i++) {
            ofVec3f v = box.getVertex(i) * mat;
            ofVec3f n = ((box.getNormal(i) + v) * mat - (v * mat)).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            
            box.addColor(c);
        }
        mesh.append(box);
    };
    
    ofVboMesh mesh;
};
