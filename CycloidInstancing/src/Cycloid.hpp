#include "ofMain.h"

class CycloidInst {
public:
    CycloidInst(){};
    void setup(){
        
        num = floor(ofRandom(1.0)*20.) + 20;
        
        float coin = ofRandom(1.0);
        ofFloatColor col;
        if (coin < 0.9) col.setHsb(0.6, 0.4, 0.6);
        else col.set(1.5, 0.9, 0.9);
        
        shader.load("shader/scene/shader");
        shader.begin();
        shader.setUniform1i("num", num);
        shader.end();
        
        mesh = ofMesh::box(1.,1.,1., 1,1,1);
        for (int i = 0; i < mesh.getNumIndices(); i++){
            mesh.addColor(col);
        }
        coin = ofRandom(1.0);
        
        float d, w, h;
        
        if (coin < 0.33) {
            d = ofRandom(1.0, 5.0) * 5.;
            w = ofRandom(1.0, 5.0) * 5.;
            h = ofRandom(1.0, 5.0) * 100.;
        } else if (coin < 0.66) {
            d = ofRandom(1.0, 5.0) * 5.;
            w = ofRandom(1.0, 5.0) * 100.;
            h = ofRandom(1.0, 5.0) * 50.;
        } else {
            d = ofRandom(1.0, 5.0) * 20.;
            w = ofRandom(1.0, 5.0) * 20.;
            h = ofRandom(1.0, 5.0) * 20.;
        }
        
        
        boxScale = ofVec3f(w, h, d);
//        boxRotate = ofVec3f(0.3, 0.0, 0.0);
        radius = 400. * ofRandom(0.8, 2.0);
        rotation = ofVec3f(ofRandom(PI), ofRandom(PI), ofRandom(PI));
    };
    void update(){
        t += 0.01;
    };
    void draw(ofCamera cam, bool isShadow){
        
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        
        shader.begin();
        shader.setUniform1i("isShadow", isShadow?1:0);
        shader.setUniformMatrix4f("normalMatrix", normalMatrix);
        shader.setUniform1f("farClip", cam.getFarClip());
        shader.setUniform1f("nearClip", cam.getNearClip());
        
        shader.setUniform1f("time", ofGetElapsedTimef()*0.2);
        shader.setUniform1f("radius", radius * (1.5 + cos(ofGetElapsedTimef()*0.2+num)));
        shader.setUniform3f("boxScale", boxScale);
        shader.setUniform3f("rot", rotation);
        
        mesh.drawInstanced(OF_MESH_FILL, num);
        shader.end();
    };
    
private:
    ofVboMesh mesh;
    ofShader shader;
    
    ofVec3f boxScale;
    ofVec3f boxRotate;
    ofVec3f rotation;
    float radius;
    
    float t = 0.0;
    int num;
    
};
