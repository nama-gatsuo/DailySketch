#include "ofMain.h"

class FSWarm {
public:
    FSWarm(){
        ofVec3f ov[6] = {
            ofVec3f(1,0,0), ofVec3f(-1,0,0), ofVec3f(0,1,0),
            ofVec3f(0,-1,0), ofVec3f(0,0,1), ofVec3f(0,0,-1)
        };
        unsigned oi[24] = {
            0, 2, 4, 0, 4, 3, 0, 3, 5, 0, 5, 2,
            1, 2, 5, 1, 5, 3, 1, 3, 4, 1, 4, 2
        };
        
        for (int i = 0; i < 24; i += 3) {
            ofVec3f v1 = ov[oi[i]] * 0.1;
            ofVec3f v2 = ov[oi[i+1]] * 0.1;
            ofVec3f v3 = ov[oi[i+2]] * 0.1;
            
            ofVec3f n = (v3 - v1).getNormalized().getCrossed((v2 - v1).getNormalized());
            n.normalize();
            
            mesh.addVertex(v1);
            mesh.addVertex(v2);
            mesh.addVertex(v3);
            
            mesh.addNormal(n);
            mesh.addNormal(n);
            mesh.addNormal(n);
        }
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    };
    
    ofVec3f getCurvePoint(ofVec3f &params1, ofVec3f &params2, float t, float phase){
        ofVec3f v = ofVec3f(
                            sin(params1.x * t + (1 + sin(params2.x * t + phase) * 0.5)),
                            sin(params1.y * t + (1 + sin(params2.y * t + phase) * 0.5)),
                            sin(params1.z * t + (1 + sin(params2.z * t + phase) * 0.5))
                            );
        return v;
    };
    void update(){
        
        t0 += 0.001;
        phase += 0.00279;
        
    };
    
    void draw(){
        ofSeedRandom(0);
        for (int ri = 0; ri < 20; ri++) {
            
            ofVec3f params1 = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)) * 6;
            ofVec3f params2 = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)) * 20;
            
            ofVec3f Pp = getCurvePoint(params1, params2, t0 - dt, phase);
            ofVec3f P1 = getCurvePoint(params1, params2, t0, phase);
            ofVec3f T1 = P1 - Pp;
            float t = t0 - dt;
            
            for (int i = 0; i < 40; i++) {
                
                ofVec3f P = getCurvePoint(params1, params2, t, phase);
                ofVec3f T = P - P1;
                ofVec3f N = T - T1;
                ofVec3f B = T.getCrossed(N).getNormalized();
                
                ofVec3f xAxis = B;
                ofVec3f zAxis = T.getNormalized();
                ofVec3f yAxis = xAxis.getCrossed(zAxis).getNormalized();
                
                ofMatrix4x4 mat = ofMatrix4x4(
                                              xAxis.x, xAxis.y, xAxis.z, 0.0,
                                              yAxis.x, yAxis.y, yAxis.z, 0.0,
                                              zAxis.x, zAxis.y, zAxis.z, 0.0,
                                              P.x, P.y, P.z, 1.0
                                              );
                
                ofPushMatrix();
                ofScale(1000, 1000, 1000);
                ofMultMatrix(mat);
                
                mesh.draw();
                
                ofPopMatrix();
                
                P1 = P;
                T1 = T;
                t += dt;
                
            }
        
        }
        
    };
    
private:
    
    float dt = 0.005;
    float t0 = 20.;
    float phase = 20.;
    
    ofVboMesh mesh;
};
