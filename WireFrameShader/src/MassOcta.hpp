#include "ofMain.h"

class MassOcta {
public:
    void setup(){
        
        for (int i = 0; i < 18; i++) {
            ofMatrix4x4 m;
            m.glScale(100, 100, 100);
            m.glRotate(20*i, 0, 1, 0);
            
            for (int j = 0; j < 36; j++) {
                
                m.glTranslate(0., 0.5, 0.);
                m.glRotate(10, 0, 0, 1);
                
                createOcta(&m);
            }
            
            createOcta(&m);
        }
        
    }
    
    void createOcta(ofMatrix4x4 * mat) {
        ofVboMesh m;
        vector<ofVec3f> vecs;
//        vector<ofVec3f> normal;
        for (int i = 0; i < oi.size(); i++) {
            vecs.push_back(ov[ oi[i] ] * *mat);
        }
        
        m.addVertices(vecs);
        
        mesh.append(m);
        
    }
    
    void draw() {
        mesh.draw();
    }
    
private:
    ofVboMesh mesh;
    vector<ofVec3f> ov = {
        ofVec3f(1,0,0), ofVec3f(-1,0,0), ofVec3f(0,1,0),
        ofVec3f(0,-1,0), ofVec3f(0,0,1), ofVec3f(0,0,-1)
    };
    vector<unsigned> oi = {
        0, 2, 4, 0, 4, 3, 0, 3, 5, 0, 5, 2,
        1, 2, 5, 1, 5, 3, 1, 3, 4, 1, 4, 2
    };
};
