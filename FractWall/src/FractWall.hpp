#pragma once
#include "ofMain.h"

namespace CustomObj {
    class FractWall {
    public:
        FractWall(){};
        void setup(){
            createRoom(ofMatrix4x4(), initialSize, 0);
        };
        void draw(){
            mesh.draw();
        };
        
    private:
        
        void createRoom(ofMatrix4x4 mat, float size, int level){
            
            for (int i = 0; i < 4; i++) {
                
                ofMatrix4x4 m = mat;
                m.glRotate(90 * i, 0, 1, 0);
                m.glTranslate(size * 0.5, 0, 0);
                
                m.glScale(size * width, (depth - level) * 40 + 10, size * (1.0 + width));
                createBox(m, level);
                
            }
            
            if (level == depth) {
                
                return;
                
            } else {
                
                for (int i = 0; i < 4; i++) {
                    
                    ofMatrix4x4 m = mat;
                    m.glRotate(90*i, 0, 1, 0);
                    m.glTranslate(size * root_two * 0.7, 0, 0);
                    m.glRotate(45, 0, 1, 0);
                    createRoom(m, size * k, level+1);
                    
                }
                
            }
            
            
            
        };
        void createBox(ofMatrix4x4 mat, int level){
            ofMesh box = ofMesh::box(1.0, 1.0, 1.0, 1, 1, 1);
            int iNum = mesh.getNumVertices();
            float cp = level + 1.0;
            
            for (int i = 0; i < box.getNumVertices(); i++) {
                ofVec3f v = box.getVertex(i);
                mesh.addVertex(v * mat);
                mesh.addNormal( ((box.getNormal(i) + v) * mat - (v * mat)).normalize());
                mesh.addColor(ofFloatColor(c.r * cp, c.g * cp, c.b * cp));
            }
            
            for (int i = 0; i < box.getNumIndices(); i++) {
                mesh.addIndex(box.getIndex(i) + iNum);
            }
            
            
        };
        
        ofVboMesh mesh;
        const int depth = 5;
        const float k = 0.9;
        const float width = 0.01;
        const float height = 1.0;
        const float initialSize = 512;
        ofFloatColor c = ofFloatColor(0.1, 0.16, 0.23);
        
        const float root_two = sqrt(2.0);
    };
};

