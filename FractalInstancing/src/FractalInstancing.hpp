#include "ofMain.h"

class FractInst {
public:
    void setup(){
        int depth = 7;
        num = pow(4., depth);
        shader.load("shader/scene/shader");
        mesh = ofMesh::box(1.,1.,1., 1,1,1);
        
        ofFloatColor col;
        col.set(0.7);
        
        for (int i = 0; i < mesh.getNumIndices(); i++){
            mesh.addColor(col);
        }
        
    };
    void update(float speed){
//        an = (_an - an) * speed + an;
        dt = (_dt - dt) * speed + dt;
        ds = (_ds - ds) * speed + ds;
        bs = (_bs - bs) * speed + bs;
        slp = (_slp - slp) * speed + slp;
    };
    
    void draw(ofCamera cam, bool isShadow){
        
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        
        shader.begin();
        shader.setUniform1i("isShadow", isShadow?1:0);
        shader.setUniformMatrix4f("normalMatrix", normalMatrix);
        shader.setUniform1f("farClip", cam.getFarClip());
        shader.setUniform1f("nearClip", cam.getNearClip());
        
        shader.setUniform1f("dt", dt * 20.);
        shader.setUniform3f("bs", bs);
        shader.setUniform1f("ds", ds);
        shader.setUniform1f("an", an);
        shader.setUniform1f("slp", 2.);
        mesh.drawInstanced(OF_MESH_FILL, num);
        shader.end();
    };
    
    void randomize(){
        
        _dt = ofRandom(1.0)*0.5+0.5;
        _ds = ofRandom(1.0)*0.2+0.6;
        
        float coin = ofRandom(1.);
        if (coin < 0.33) {
            an = 3.0;
        } else if (coin < 0.66){
            an = 4.0;
        } else {
            an = 6.;
        }
        
        coin = ofRandom(1.);
        if (coin < 0.33) {
            _bs = ofVec3f(0.5, ofRandom(40.), 0.5);
        } else if (coin < 0.66){
            _bs = ofVec3f(ofRandom(40.), 0.5, 0.5);
        } else {
            _bs = ofVec3f(0.5, 0.5, ofRandom(40.));
        }
        
        coin = ofRandom(1.);
        if (coin < 0.3 ) {
            _slp = 2.0;
        } else {
            _slp = 2.0;
        }
        
    };
private:
    ofVboMesh mesh;
    ofShader shader;
    int num;
    float dt, ds, an;
    float _dt = 1., _ds = 1., _an = 3.;
    ofVec3f bs, _bs;
    float slp, _slp;
};
