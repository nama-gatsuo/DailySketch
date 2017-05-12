#include "ofMain.h"

class IcosaSurface {
public:
    void setup(){
        createMesh();
        createTex();
    };
    
    void update(){};
    
    void draw(){
        ofPushStyle();
        
        ofSetColor(128, 255, 200);
        
        fbo.getTexture().bind(0);
        mesh.draw(OF_MESH_FILL);
        fbo.getTexture().unbind(0);
        
        ofPopStyle();
        
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
        
        ofVec3f v0, v1, v2, n;
        ofVec2f tc[3];
        for (int i = 0; i < 20; i++) {
            
            v0 = verts[faces[i*3]];
            v1 = verts[faces[i*3 + 1]];
            v2 = verts[faces[i*3 + 2]];
            
            n = (v1 - v0).cross(v2 - v0).normalize();
            
            mesh.addVertex(v0 * scale);
            mesh.addVertex(v1 * scale);
            mesh.addVertex(v2 * scale);
            
            float r = w / 2;
            for (int j = 0; j < 3; j++) {
                tc[j] = ofVec2f(r * cos(TWO_PI/3 * j) + w/2, r * sin(TWO_PI/3 * j) + w/2);
                mesh.addTexCoord(tc[j]);
                mesh.addNormal(n);
            }
        }
    };
    
    void createTex(){
        
        fbo.allocate(w, w);
        
        fbo.begin();
        ofClear(0);
        ofPushMatrix();
        
        ofSetColor(255);
        ofTranslate(w/2, w/2);
        ofVec2f a, b, c;
        for (int i = 0; i < 3; i++) {
            ofPushMatrix();
            ofRotate(120*i);
            
            a = ofVec2f(w/2, 0);
            b = ofVec2f(w/4 * cos(PI/3), w/4 * sin(PI/3));
            c = ofVec3f(0,0);
            createSub(a,b,c);
            drawSub();
            
            a = ofVec2f(w/2, 0);
            b = ofVec2f(w/4 * cos(PI/3), - w/4 * sin(PI/3));
            c = ofVec3f(0,0);
            createSub(a,b,c);
            drawSub();
            
            ofPopMatrix();
        }
        
        ofPopMatrix();
        fbo.end();
        
    };
    
    void createSub(ofVec2f a, ofVec2f b, ofVec2f c){
        
        sub.clear();
        int col = 128;
        
        vector<vector<ofVec2f>> tmp;
        for (int i = 0; i <= col; i++) {
            
            tmp.push_back(vector<ofVec2f>());
            
            ofVec2f aj = a.interpolate(c, (float)i / col);
            ofVec2f bj = b.interpolate(c, (float)i / col);
            
            int row = col - i;
            
            for (int j = 0; j <= row; j++) {
                if (j == 0 && i == col) {
                    tmp[i].push_back(aj);
                } else {
                    tmp[i].push_back(aj.interpolate(bj, (float)j / row));
                }
                
            }

        }
        
        for (int i = 0; i < col; i++) {
            for (int j = 0; j < 2 * (col - i) -1; j++) {
                
                int k = floor(j / 2);
                if (j % 2 == 0) {
                    sub.push_back(tmp[i][k+1]);
                    sub.push_back(tmp[i+1][k]);
                    sub.push_back(tmp[i][k]);
                } else {
                    sub.push_back(tmp[i][k+1]);
                    sub.push_back(tmp[i+1][k+1]);
                    sub.push_back(tmp[i+1][k]);
                }
            }
        }
    };
    void drawSub(){
        float seed = 0.0;
        for (int i = 0; i < sub.size(); i += 3) {
            seed += 0.18;
            float n = ofNoise(seed);
                
            if (n < 0.35) {
                glBegin(GL_TRIANGLES);
                
                glVertex2f(sub[i].x, sub[i].y);
                glVertex2f(sub[i+1].x, sub[i+1].y);
                glVertex2f(sub[i+2].x, sub[i+2].y);
                glEnd();
            }
            
        }
        
    };
    
private:
    ofVboMesh mesh;
    ofFbo fbo;
    vector<ofVec2f> sub;
    
    int w = 1024;
    float scale = 300;
};

