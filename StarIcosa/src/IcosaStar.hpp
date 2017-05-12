#include "ofMain.h"

class IcosaStar {
public:
    void setup(){
        float t = (1.0 + sqrt(5)) / 2;
        phv = {
            ofVec3f(-1, t,  0), ofVec3f(1, t, 0), ofVec3f(-1, -t, 0), ofVec3f(1, -t,  0),
            ofVec3f(0, -1,  t), ofVec3f(0, 1, t), ofVec3f(0, -1, -t), ofVec3f(0,  1, -t),
            ofVec3f(t,  0, -1), ofVec3f(t, 0, 1), ofVec3f(-t, 0, -1), ofVec3f(-t, 0,  1)
        };
    };
    void update();
    void draw(){
        ofSetColor(255);
        
        ofVec3f v0, v1, v2, v3;
        
        for (auto target : phv) {
            int num = 12;
            
            for (int j = 0; j < 12; j++) {
                
                for (int i = 0; i < num; i++) {
                    
                    float n1 = ofNoise(j*0.11,i*0.11);
                    float n2 = ofNoise(j*0.11,i*0.11);
                    
                    if (n1 > 0.7) ofNoFill();
                    else ofFill();
                    
                    float r1 = 0.03 * j + n1 * 0.2;
                    float r2 = 0.03 * j + n2 * 0.2;
                    
                    float t1 = 2.4 - j * 0.15;
                    float t2 = 2.3 - j * 0.15;
                    
                    glBegin(GL_TRIANGLE_STRIP);
                    
                    v0 = ofVec3f(r1 * cos(TWO_PI / num * i), r1 * sin(TWO_PI / num * i), t1);
                    la(&v0, &target);
                    
                    v1 = ofVec3f(r2 * cos(TWO_PI / num * i), r2 * sin(TWO_PI / num * i), t2);
                    la(&v1, &target);
                    
                    v2 = ofVec3f(r1 * cos(TWO_PI / num * (i+1)), r1 * sin(TWO_PI / num * (i+1)), t1);
                    la(&v2, &target);
                    
                    v3 = ofVec3f(r2 * cos(TWO_PI / num * (i+1)), r2 * sin(TWO_PI / num * (i+1)), t2);
                    la(&v3, &target);
                    
                    
                    ofVec3f n = (v1 - v0).cross(v2 - v0).normalize();
                    
                    glVertex3f(v0.x*100, v0.y*100, v0.z*100);
                    glVertex3f(v1.x*100, v1.y*100, v1.z*100);
                    glVertex3f(v2.x*100, v2.y*100, v2.z*100);
                    glVertex3f(v3.x*100, v3.y*100, v3.z*100);
                    glNormal3f(n.x, n.y, n.z);
                    
                    glEnd();
                }
            }
            
        }

    };
private:
    void la(ofVec3f * v, ofVec3f * target) {
        
        ofVec3f rel = - target->normalize();
        float lat = acos(rel.y) - HALF_PI;
        float lon = atan2(rel.x, rel.z);
        
        ofMatrix4x4 m;
        m.rotateRad(lat, 1, 0, 0);
        m.rotateRad(lon, 0, 1, 0);
        *v = *v * m;
    };
    
    vector<ofVec3f> phv;
};
