#pragma once
#include "ofMain.h"

class TriPat {
public:
    TriPat(){};
    void setup(){
        
        num = floor(ofRandom(2.0, 8.0));
        float z = ofRandom(-800, 800);
        c.set(0.5, 0.8, 0.8 + ofRandom(0.8));
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        createRandomSeed();
        
        unsigned yn = 4;
        unsigned xn = 4;
        
        float r = 300;
        float dh = r * 1.5;
        float dw = r * sqrt(3.);
        for (int i = 0; i < yn; i++) {
            ofVec3f v[3];
            
            for (int j = 0; j < xn; j++) {
                
                ofVec3f shift(dw * (j-xn*0.5), dh * (i-yn*0.5), z);
                if (i%2==0) shift.x -= dw * 0.5;
                
                v[0] = ofVec3f(0,r,0) + shift;
                v[1] = ofVec3f(-r*sqrt(3.)*0.5,-r*0.5,0) + shift;
                v[2] = ofVec3f(r*sqrt(3.)*0.5,-r*0.5,0) + shift;
                createTri(v[0], v[1], v[2]);
                
                v[0] = ofVec3f(r*sqrt(3.)*0.5,-r*0.5,0) + shift;
                v[1] = ofVec3f(0,r,0) + shift;
                v[2] = ofVec3f(r*sqrt(3.),r,0) + shift;
                createTri(v[0], v[1], v[2]);
            }
            

        }
        
    };
    void draw(){
        mesh.draw();
    };
private:
    void createRandomSeed(){
        randomSeeds.clear();
        for (int i = 0; i < num; i++) {
            vector<float> trs;
            for (int j = 0; j < num-i; j++) {
                trs.push_back(ofRandom(1.));
            }
            randomSeeds.push_back(trs);
        }
    };
    void createTri(ofVec3f v1, ofVec3f v2, ofVec3f v3){
        ofVec3f v[3];
        v[0] = v1;
        v[1] = v2;
        v[2] = v3;
        
        ofVec3f center = (v[0] + v[1] + v[2]) / 3.0;
        
        for (int i = 0; i < 3; i++) {
            int i1 = i, i2 = i+1;
            if (i == 2) i2 = 0;
            
            createPat(v[i1], center, (v[i2] + v[i1]) * 0.5);
            createPat(v[i2], center, (v[i2] + v[i1]) * 0.5);
            
        }
        
    };
    void createPat(ofVec3f v1, ofVec3f v2, ofVec3f v3){
        
        for (int i = 0; i < num; i++) {
            
            ofVec3f start = v1.getInterpolated(v3, (float)i/num);
            ofVec3f next;
            for (int j = 0; j < num-i; j++){
                
                ofVec3f target;
                if (randomSeeds[i][j] < 0.5) {
                    target = (v2 - v1) * (1.0 / num);
                } else if (randomSeeds[i][j] < 0.85) {
                    target = (v3 - v1) * (1.0 / num);
                } else {
                    ofVec3f t1 = (v2 - v1) * (1.0 / num);
                    ofVec3f t2 = (v3 - v1) * (1.0 / num);
                    
                    target = t1 * 2.0 - t2;
                }
                
                next = start + target;
                
                addBox(start, next, ofNoise(i*randomSeeds[i][j], j*randomSeeds[i][j]));
                
                start = next;
            }
        }
        
    };
    void addBox(ofVec3f start, ofVec3f end, float width){
        
        ofVec3f rel = (end - start).normalize();
        float lat = acos(rel.y) - HALF_PI;
        float lon = atan2(rel.x, rel.z);
        
        ofMatrix4x4 m;
        m.rotateRad(lat, 1, 0, 0);
        m.rotateRad(lon, 0, 1, 0);
        
        float d = end.distance(start);
        float h = 48. / num;
        float w = 48. / num;
        
        ofMesh box = ofMesh::box(w,h,d, 1,1,1);
        for (int i = 0; i < box.getNumVertices(); i++) {
            ofVec3f v = (box.getVertex(i) + ofVec3f(0,0,d*0.5)) * m + start;
            ofVec3f n = ((box.getNormal(i) + v) * m - (v * m)).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            
            box.addColor(c);
        }
        mesh.append(box);
        
    };
    ofFloatColor c;
    ofVboMesh mesh;
    unsigned num = 6;
    vector<vector<float>> randomSeeds;
};
