#include "ofMain.h"

class SymOcta {
public:
    SymOcta(){};
    void setup(){
        
        for (int i = 0; i < 6; i++) {
            pyra(m[i]);
        }
        
    };
    
    void addBox(ofMatrix4x4& _m, float length, bool light){
        
        
        ofMesh box = ofMesh::box(BOX_WIDTH,BOX_WIDTH,length+BOX_WIDTH,  1,1,1);
        
        for (int i = 0; i < box.getNumVertices(); i++) {
            
            ofVec3f v = box.getVertex(i) * _m;
            ofVec3f n = ((box.getNormal(i) + box.getVertex(i)) * _m - v).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            
            if (light) {
                box.addColor(ofFloatColor(0.7, 1.2, 1.2, 1.));
            } else {
                box.addColor(ofFloatColor(0.5));
            }
            
        }
        
        mesh.append(box);
        
    };
    
    void pyra(ofMatrix4x4& _m){
        ofSeedRandom(0);
        for (int i = 0; i < NUM_HIEGHT; i++) {
            
//            if (ofRandom(1.) < 0.4) continue;
            
            ofMatrix4x4 mat(_m);
            float outer = SIZE / NUM_HIEGHT * i;
            
            mat.glTranslate(0, outer, 0);
            
            float s = ofRandom(0.05, 0.4);
            
            for (int j = 0; j < 4; j++) {
                
                if (ofRandom(1.) < 0.5) continue;
                
                ofMatrix4x4 mat1(mat);
                mat1.glRotate(90*j, 0,1,0);
                mat1.glTranslate(outer - outer * s, 0, 0);
                
                bool bLight = ofRandom(1.) > 0.9;
                
                for (int k = 0; k < 4; k++) {
                    ofMatrix4x4 mat2(mat1);
                    mat2.glRotate(45+90*k, 0, 1, 0);
                    mat2.glTranslate(outer * s / sqrt(2.), 0, 0);
                    
                    addBox(mat2, outer * s * 2. / sqrt(2.), bLight);
                    
                }
                
            }
            
        }
        
    };
    
    void draw(){
        
        mesh.draw();
        
    };
private:
    const unsigned NUM_HIEGHT = 30;
    const float SIZE = 600;
    const float BOX_WIDTH = 10;
    
    ofVboMesh mesh;
    
    ofMatrix4x4 m[6] = {
        // y -> y posi
        ofMatrix4x4(1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1),
        // y -> nega
        ofMatrix4x4(-1,0, 0,0,
                    0,-1, 0,0,
                    0, 0,-1,0,
                    0,0,0,1),
        
        // y -> x posi
        ofMatrix4x4(0, 1,0,0,
                    -1,0,0,0,
                    0, 0,-1,0,
                    0,0,0,1),
        // y -> x nega
        ofMatrix4x4(0,-1,0,0,
                    1,0, 0,0,
                    0,0, 1,0,
                    0,0,0,1),
        
        // y -> z posi
        ofMatrix4x4(1,0,0,0,
                    0,0,-1,0,
                    0,-1,0,0,
                    0,0,0,1),
        // y -> z nega
        ofMatrix4x4(-1,0,0,0,
                    0,0,1,0,
                    0,1,0,0,
                    0,0,0,1)
        
    };
    
    
};
