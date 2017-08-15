#include "ofMain.h"


class MeshEarth {
public:
    void setup(){
        
        ofImage height;
        ofImage color;
        
        color.load("img/color.jpg");
        height.load("img/height.jpg");
        sea.load("img/sea.jpg");
        
        shader.load("shader/shader");
        shader.begin();
        shader.setUniformTexture("sea", sea.getTexture(), 0);
        shader.end();
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        int res = 1000;
        float radius = 300.;
        
        for (int si = 0; si < res+1; si++) {
            for (int ti = 0; ti < res*2+1; ti++) {
                float s = PI / res * si;
                float t = PI / res * ti;
                
                float h = height.getColor(height.getWidth() / (res*2.) * ti,
                                          height.getHeight() / res * si).r / 12.;
                
                float r = radius * (h * 5000. / 6371000 + 1.);
                
                ofVec3f v;
                v.x = r * sin(t) * sin(s);
                v.z = r * cos(t) * sin(s);
                v.y = r * cos(s);
                
                mesh.addVertex(v);
                mesh.addTexCoord(ofVec2f(0.5 / res * ti, 1. / res * si));
                
                ofFloatColor c = color.getColor(color.getWidth() / (res*2.) * ti,
                                                color.getHeight() / res * si);
                mesh.addColor(c);
            }
        }
        
        for (int si = 0; si < res; si++) {
            for (int ti = 0; ti < res*2+1; ti++) {
                
                mesh.addIndex(ti + si * (res * 2 + 1));
                mesh.addIndex(ti + (si+1) * (res * 2 + 1));
            }
        }
    };
    void draw(){
        shader.begin();
        mesh.draw(OF_MESH_WIREFRAME);
        shader.end();
    };
    
private:
    ofVboMesh mesh;
    ofShader shader;
    
    ofImage sea;

};
