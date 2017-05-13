#include "ofMain.h"

class FractSubIcosa {
public:
    void setup(){
        createMesh();
    };
    void update(){};
    void draw(){
        mesh.draw();
    };
    
    void createMesh(){
        float t = (1.0 + sqrt(5)) / 2;
        
        ofVec3f verts[12] = {
            ofVec3f(-1, t,  0), ofVec3f(1, t, 0), ofVec3f(-1, -t, 0), ofVec3f(1, -t,  0),
            ofVec3f(0, -1,  t), ofVec3f(0, 1, t), ofVec3f(0, -1, -t), ofVec3f(0,  1, -t),
            ofVec3f(t,  0, -1), ofVec3f(t, 0, 1), ofVec3f(-t, 0, -1), ofVec3f(-t, 0,  1)
        };
        int faces[60] = {
            0, 11,  5,    0,  5,  1,    0,  1,  7,    0,  7, 10,    0, 10, 11,
            1,  5,  9,    5, 11,  4,   11, 10,  2,   10,  7,  6,    7,  1,  8,
            3,  9,  4,    3,  4,  2,    3,  2,  6,    3,  6,  8,    3,  8,  9,
            4,  9,  5,    2,  4, 11,    6,  2, 10,    8,  6,  7,    9,  8,  1
        };
        
        ofVec3f v[3];
        for (int i = 0; i < 60; i += 3){
            v[0] = verts[faces[i]] * scale;
            v[1] = verts[faces[i+1]] * scale;
            v[2] = verts[faces[i+2]] * scale;
            
            createFace(v, 0);
            
        }
        
        
    };
    void createFace(const ofVec3f * v, int level){
        
        if (level == LOOP_NUM) {
            
            ofVec3f n = - (v[2] - v[0]).cross(v[1] - v[0]).normalize();
            ofFloatColor c;
            if (mesh.getNumVertices()%81 == 15) c.setHsb(0.4, 0.8, 1.0);
            else c.setHsb(0.9, 0.1, 0.2);
            
            for (int i = 0; i < 3; i++) {
                mesh.addVertex(v[i] * 1.0);
                mesh.addNormal(n);
                mesh.addColor(c);
            }
            
        } else {
            level++;
            float len = (v[1] - v[0]).length();
            float sign = pow(-1.0, level);
            
            ofVec3f center = (v[0] + v[1] + v[2]) / 3.0;
            ofVec3f vperp = sign * (v[2] - v[0]).cross(v[1] - v[0]).normalize() * depth / (float)level + center;
            
            for (int i = 0; i < 3; i++) {
                ofVec3f tv[3];
                
                if (i == 2) {
                    tv[0] = v[i];
                    tv[1] = vperp;
                    tv[2] = v[0];
                } else {
                    tv[0] = v[i];
                    tv[1] = vperp;
                    tv[2] = v[i+1];
                }
                
                createFace(tv, level);
            }
            
        }
        
    };
    
private:
    ofVboMesh mesh;
    float scale = 300;
    float depth = 350.;
    int LOOP_NUM = 7;
};
