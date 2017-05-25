#pragma once

#include "ofMain.h"

class RandomJoint {
public:
    RandomJoint(){};
    void setup(){
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        createMesh();
        ofSetSphereResolution(2);
    };
    void draw(){
        mesh.draw();
    };
    
private:
    void createMesh(){
        
        vector<ofVec3f> randomCoord;
        vector<ofVec3f> joints;
        
        const int jointNum = 40;
        const int partsNum = 6;
        
        float radius = 768.0;
        float heightBallance = 0.8;
        
        float threshold = 180.0;
        
        for (int i = 0; i < jointNum; i++) {
            
            float xMax = radius * cos(PI/partsNum);
            float yMax = radius * sin(PI/partsNum);
            
            float h = radius * heightBallance;
            
            ofVec3f p;
            p.x = ofRandom(0.03, 1.0) * xMax;
            p.y = ofRandom(0.03, 1.0) * yMax;
            p.z = ofRandom(0.03, 1.0) * h - h * 0.5;
            
            randomCoord.push_back(p);
            
        }
        
        
        for (int i = 0; i < partsNum; i++) {
            ofMatrix4x4 mat;
            mat.glRotate(60 * i, 0, 1, 0);
            
            for (int j = 0; j < jointNum; j++) {
                joints.push_back( randomCoord[j] * mat );
            }
        }
        
        int n = joints.size(); // jointNum * partsNum
        float thickness = 0.02;
        
        for (int i = 0; i < n; i++) {
            ofVec3f p1 = joints[i];
            createSphere(p1);
            
            for (int j = i+1; j < n; j++) {
                ofVec3f p2 = joints[j];
                float dist = p1.distance(p2);
                if (dist < threshold) {
                    createOcta(p1, p2, thickness);
                }
            }
        }
    
    };
    
    void createSphere(ofVec3f p){
        ofMesh s = ofMesh::sphere(5.0);
        for (int i = 0; i < s.getNumIndices(); i++) {
            mesh.addVertex(s.getVertex(s.getIndex(i)) + p);
            mesh.addNormal(s.getNormal(s.getIndex(i)));
            mesh.addColor(ofFloatColor(1.05));
        }
    }
    
    void createOcta(ofVec3f p1, ofVec3f p2, float thickness){
        
        float dist = p1.distance(p2);
        ofVec3f center = (p1 + p2) * 0.5;
        
        ofVec3f axisY = (p2 - p1).normalize();
        ofVec3f axisX = axisY.getCrossed(ofVec3f(0,1,0)).normalize();
        ofVec3f axisZ = axisX.getCrossed(axisY).normalize();
        
        ofVec3f belt[4];
        belt[0] = center + axisX * dist * thickness;
        belt[1] = center + axisZ * dist * thickness;
        belt[2] = center - axisX * dist * thickness;
        belt[3] = center - axisZ * dist * thickness;
        
        for (int i = 0; i < 4; i++) {
            int i1 = i;
            int i2 = i == 3 ? 0 : i+1;
            
            createFace(p1, belt[i1], belt[i2]);
            createFace(p2, belt[i2], belt[i1]);
        }
        
    };
    
    void createFace(ofVec3f p1, ofVec3f p2, ofVec3f p3){
        
        ofVec3f n = (p2 - p1).cross(p3 - p1).normalize();
        
        mesh.addVertex(p1);
        mesh.addVertex(p2);
        mesh.addVertex(p3);
        
        mesh.addNormal(n);
        mesh.addNormal(n);
        mesh.addNormal(n);
        
        mesh.addColor(ofFloatColor(0.4, 0.7, 0.9));
        mesh.addColor(ofFloatColor(0.4, 0.7, 0.9));
        mesh.addColor(ofFloatColor(0.4, 0.7, 0.9));
    }
    
    ofVboMesh mesh;
};
