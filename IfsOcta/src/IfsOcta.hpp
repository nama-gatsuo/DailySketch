#include "ofMain.h"

class IfsOcta {
public:
    IfsOcta(){};
    void setup(){
        
        
        for (int i = 0; i < 6; i++) {
            ofMatrix4x4 mat;
            mat.translate(0,300,0);
            mat.postMult(m[i]);
            itr(mat, 0);
        }
        
        
    };
    void itr(ofMatrix4x4 _m, int lev){
        
        lev++;
        if (lev != 0) {
            addBox(_m, (lev%4==0) && ofRandom(1.) > 0.8);
        }
        
        if (lev > MAX_LEV) {
            return;
        } else {
            ofMatrix4x4 mat(_m);
            
            
//            for (int j = 0; j < 3; j++) {
//                mat.preMult(m[ j*2 ]);
//
//                ofMatrix4x4 scaleMat;
//                scaleMat.glScale(0.9,0.9,0.9);
//                scaleMat.glRotate(4, 1,0,0);
//                scaleMat.glRotate(4, 0,1,0);
//                scaleMat.glRotate(1, 0,0,1);
//                mat.preMult(scaleMat);
//                mat.glTranslate(10, 40, 10);
//
//                itr(mat, lev);
//            }
            
            for (int i = 0; i < 6; i++) {

                if (i == 1) continue;

                ofMatrix4x4 mat(_m);

                mat.preMult(m[i]);

                ofMatrix4x4 scaleMat;
                scaleMat.glScale(0.6,0.5,0.6);
                mat.preMult(scaleMat);
                mat.glTranslate(0, 300, 0);

                itr(mat, lev);

            }
            
        }
        
    };
    
    void addBox(ofMatrix4x4& _m, bool light){
        
        ofMesh box = ofMesh::box(20,1000,20, 1,1,1);
        for (int i = 0; i < box.getNumVertices(); i++) {
            
            ofVec3f v = box.getVertex(i) * _m;
            ofVec3f n = ((box.getNormal(i) + box.getVertex(i)) * _m - v).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            
            if (light) {
                box.addColor(ofFloatColor(1.1, 0.9, 2., 1.));
            } else {
                box.addColor(ofFloatColor(1.));
            }
            
        }
        
        mesh.append(box);
        
    };
    
    void draw(){
        
        mesh.draw();
        
    };
private:
    const unsigned MAX_LEV = 5;
    
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
