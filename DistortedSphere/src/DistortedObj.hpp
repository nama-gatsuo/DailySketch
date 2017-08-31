#include "ofMain.h"

class DistortedObj {
public:
    void setup(int mode){
        
        if (mode == 0) mesh = ofMesh::sphere(100., 50);
        else if (mode == 1) {
            mesh = ofMesh::plane(1000, 1000, 100, 100);
            for (int i = 0; i < mesh.getNumVertices(); i++) {
                mesh.setVertex(i, mesh.getVertex(i) + ofVec3f(0,0,-300));
            }
        }
        
        shader.load("shader/scene/shader");
        
        time = 0.;
        
    };
    
    void draw(ofCamera cam, bool isShadow){
        
        shader.begin();
        shader.setUniform1i("isShadow", isShadow?1:0);
        shader.setUniform1f("farClip", cam.getFarClip());
        shader.setUniform1f("nearClip", cam.getNearClip());
        
        shader.setUniform1f("time", ofGetElapsedTimef());
        
        mesh.draw();
        shader.end();
        
    };
    
private:
    ofShader shader;
    ofVboMesh mesh;
    float time;
};
