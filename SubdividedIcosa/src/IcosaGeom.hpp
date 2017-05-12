#include "ofMain.h"

class IcosaGeom {
public:
    void setup(){
        createMesh();
    };
    void update(){};
    void draw() const {
        mesh.draw();
        
    };

private:
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
        for (int i = 0; i < 20; i++) {
            
            v[0] = verts[faces[i*3]] * scale;
            v[1] = verts[faces[i*3 + 1]] * scale;
            v[2] = verts[faces[i*3 + 2]] * scale;
            
            createFace(v);
            
        }
        
    };
    void createFace(ofVec3f * v){
        
        ofVec3f c = (v[0] + v[1] + v[2]) / 3.0;
        
        ofVec3f vp;
        for (int i = 0; i < 3; i++) {
            
            if (i == 2) {
                vp = (v[2] + v[0]) * 0.5;
                createSub(v[2], vp, c, false);
                createSub(v[0], vp, c, true);
            } else {
                vp = (v[i] + v[i+1]) * 0.5;
                createSub(v[i],   vp, c, false);
                createSub(v[i+1], vp, c, true);
                
            }
        
        }
    
    };
    void createSub(ofVec3f a, ofVec3f b, ofVec3f c, bool inv){
    
        int col = 8;
        ofVec3f normal = (a - c).cross(b - c).normalize();
        if (!inv) normal = -normal;
        
        vector<vector<ofVec3f>> tmp;
        for (int i = 0; i <= col; i++) {
            
            tmp.push_back(vector<ofVec3f>());
            
            ofVec3f aj = a.getInterpolated(c, i / (float)col);
            ofVec3f bj = b.getInterpolated(c, i / (float)col);
            
            int row = col - i;
            
            for (int j = 0; j <= row; j++) {
                
                float noise = ofNoise(0.1 + i * 0.09, 0.1 + j * 0.12);
                noise += ofNoise(i * 0.22, 0.1 + j * 0.2) * 0.5;
                float ns = floor(noise * 3.0) * 50.0;
                
                if (j == 0 && i == col) {
                    tmp[i].push_back(aj);
                } else {
                    if (i == col) ns = 0.0;
                    tmp[i].push_back(aj.getInterpolated(bj, j / (float)row) + normal * ns);
                }
                
            }
            
        }
        
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < 2 * (col - i) -1; j++) {
                
                float noise = ofNoise(0.1 + i * 0.2, 0.1 + j * 0.1);
                ofFloatColor c;
                if (noise > 0.2) c.setHsb(0.4, 0.05, 1.0);
                else c.setHsb(0.7, 0.7, 1.0);
                
                int k = (int)floor(j / 2);
                ofVec3f v[3], n;
                
                if (j % 2 == 0) {
                    
                    v[0] = tmp[i][k+1];
                    v[1] = tmp[i+1][k];
                    v[2] = tmp[i][k];
                    
                    n = (v[2] - v[0]).cross(v[1] - v[0]).normalize();
                    if (inv) n = -n;
                    
                } else {
                    v[0] = tmp[i][k+1];
                    v[1] = tmp[i+1][k+1];
                    v[2] = tmp[i+1][k];
                    
                    n = (v[2] - v[0]).cross(v[1] - v[0]).normalize();
                    if (inv) n = -n;

                }
                mesh.addVertex(v[0]);
                mesh.addVertex(v[1]);
                mesh.addVertex(v[2]);
                
                mesh.addNormal(n);
                mesh.addNormal(n);
                mesh.addNormal(n);
                
                mesh.addColor(c);
                mesh.addColor(c);
                mesh.addColor(c);
            }
        }
    
    };
    
    ofVboMesh mesh;
    float scale = 300;
    
};
