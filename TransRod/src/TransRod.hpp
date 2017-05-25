#pragma once

#include "ofMain.h"

class TransRod {
public:
    TransRod(){};
    void setup(){
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        createMesh();
    };
    void draw(){
        mesh.draw();
    };
    
private:
    void createMesh(){
        int jointNum = 10;
        float scale = 100.0;
        
        for (int i = 0; i < jointNum; i++){
            
            ofVec3f r;
            r.x = ofRandom(-2.0, 2.0) * scale;
            r.y = ofRandom(0.4, 1.0) * scale;
            r.z = ofRandom(-2.0, 2.0) * scale;
            
            randomCoords.push_back(r);
        }
        
        for (int i = 0; i < 18; i++) {
            
            for (int j = 0; j < 18; j++) {
                ofMatrix4x4 mat;
                
                
                mat.glTranslate(5*i, 0, 5*i);
                mat.glRotate(9*i, 0, 1, 0);
                mat.glRotate(6*i, 0, 0, 1);
                mat.glScale(0.5+i*0.03, 0.5+i*0.03, 0.5+i*0.03);
                
                mat.glTranslate(10*j, 0, 8*j);
                mat.glRotate(9*j, 0, 0, 1);
                mat.glRotate(9*j, 0, 1, 0);
                mat.glScale(0.5+j*0.03, 0.5+j*0.03, 0.5+j*0.03);
                
                createRod(mat);
            }

        }
        
    };
    
    void createRod(const ofMatrix4x4& mat){
        
        ofVec3f last(0,0,0);
        for (auto r : randomCoords) {
            
            ofVec3f p1 = last;
            ofVec3f p2 = p1 + ofVec3f(0, r.y, 0);
            ofVec3f p3 = p2 + ofVec3f(r.x, 0, r.z);
            
            createBox(p1 * mat, p2 * mat);
            createBox(p2 * mat, p3 * mat);
            
            last = p3;
        }
        
    };
    
    void createBox(const ofVec3f& p1, const ofVec3f& p2){
        
        ofFloatColor c;
        if (ofRandom(1.0) > 0.1) c.setHsb(0.6, 0.5, 0.6);
        else c.setHsb(0.1, 0.5, 1.0);
        
        ofMatrix4x4 mat;
        ofMatrix4x4 rotMat;
        
        ofVec3f center = (p1 + p2) * 0.5;
        mat.glTranslate(center.x, center.y, center.z);
        
        ofVec3f lookAt = (p2 - p1).normalize();
        rotMat.makeRotationMatrix(ofVec3f(0,1,0), lookAt);
        mat = rotMat * mat;
        
        float dist = p1.distance(p2);
        mat.glScale(5, dist, 5);
        
        ofMesh box = ofMesh::box(1.0,1.0,1.0, 1,1,1);
        int iNum = mesh.getNumVertices();
        
        for (int i = 0; i < box.getNumVertices(); i++) {
            ofVec3f v = box.getVertex(i);
            mesh.addVertex(v * mat);
            mesh.addNormal( ((box.getNormal(i) + v) * mat - (v * mat)).normalize() );
            mesh.addColor(c);
        }
        for (int i = 0; i < box.getNumIndices(); i++) {
            mesh.addIndex(box.getIndex(i) + iNum);
        }
    };
    
    vector<ofVec3f> randomCoords;
    ofVboMesh mesh;
    
    
};
