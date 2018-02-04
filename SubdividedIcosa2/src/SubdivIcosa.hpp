#include "ofMain.h"

class SubdivIcosa {
public:
    SubdivIcosa(){};
    void setup(){
        
        ofMesh base = ofMesh::icosphere(SIZE, 0);
        for (int i = 0; i < 20; i ++) {
            
            ofSeedRandom(0);
            ofVec3f v[3];
            v[0] = base.getVertex(base.getIndex(i*3));
            v[1] = base.getVertex(base.getIndex(i*3+1));
            v[2] = base.getVertex(base.getIndex(i*3+2));
            
            itr(v, 0);
            
        }
        
    };
    void itr(ofVec3f * v, int lev){
        
        if (lev > MAX_LEV) {
            createTri(v);
            return;
        }
        
        ofVec3f n = (v[2] - v[0]).getCrossed(v[1] - v[0]).getNormalized();
        ofVec3f c = (v[0] + v[1] + v[2]) / 3.;
        lev++;
        
        for (int i = 0; i < 3; i++) {
        
            ofVec3f nv[3];
            
            nv[0] = c + n * SIZE * H_FACTOR * pow(0.53, lev);
            nv[1] = v[i];
            nv[2] = i==2 ? v[0] : v[i+1];
            
            float s = (1. - F_FACTOR) * 0.5;
            ofVec3f nc = c * F_FACTOR + (nv[1] + nv[2]) * s;
            
            for (int j = 0; j < 3; j++) {
                
                ofVec3f nnv[3];
                nnv[0] = nc;
                nnv[1] = nv[j];
                nnv[2] = j==2 ? nv[0] : nv[j+1];
                
                ofVec3f n = (nnv[2] - nnv[0]).getCrossed(nnv[1] - nnv[0]).getNormalized();
                
                if (j == 1) {
                    if (lev == 1) continue;
                    createTri(nnv);
                } else {
                    itr(nnv, lev);
                }
                
            }
            
        }
        
    };
    
    void createTri(ofVec3f * v){
        mesh.addVertex(v[0]);
        mesh.addVertex(v[1]);
        mesh.addVertex(v[2]);
        
        ofFloatColor c;
        if (ofRandom(1.) < 0.01) c = ofFloatColor(0.5, 1.3, 2.);
        else c = ofFloatColor(0.1);
        
        ofVec3f n = (v[2] - v[0]).getCrossed(v[1] - v[0]).getNormalized();
        
        for (int i = 0; i < 3; i++) {
            mesh.addColor(c);
            mesh.addNormal(n);
        }

    }
    
    void draw(){
        
        mesh.draw(OF_MESH_WIREFRAME);
        
    };
private:
    const int MAX_LEV = 4;
    const float SIZE = 800;
    const float H_FACTOR = -0.54;
    const float F_FACTOR = 0.33;
    
    ofVboMesh mesh;
    
    
    
    
};

