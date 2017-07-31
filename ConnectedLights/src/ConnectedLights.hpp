#pragma once
#include "ofMain.h"
#include "CommonUtil.hpp"

class Particle {
public:
    SmoothPoint pos;
    ofVboMesh lines;
    
    int interval = 120;
    unsigned int cnt;
    float threshold = 300.;
    
    
    Particle(){
//        interval = floor(ofRandom(120, 480));
        pos.setSpeed(ofRandom(0.2, 1.0) * 0.03);
        cnt = 0;
        
        lines.setMode(OF_PRIMITIVE_POINTS);
        pos.to(ofPoint(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500)));
    };
    
    void update(vector<Particle> * ps){
        cnt++;
        if (cnt % interval == 0) {
            pos.to(ofPoint(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500)));
            cnt = 0;
        }
        
        pos.update();
        lines.clearVertices();
        
        for (int i = 0; i < ps->size(); i++) {
            
            float length = pos.distance(ps->at(i).pos);
            if (length > 0. && length < threshold) {
                lines.addVertex(ps->at(i).pos);
            }
        }
        
        
    }
};

class ConnectedLights {
public:
    void setup(){
        
        gbShader.load("shader/scene/gb");
        
        lShader.setGeometryInputType(GL_POINTS);
        lShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
        lShader.setGeometryOutputCount(24);
        
        lShader.load("shader/scene/lines.vert", "shader/scene/lines.frag", "shader/scene/lines.geom");
        
        for (int i = 0; i < num; i++) {
            
            ps.push_back(Particle());
        
        }
        
        p = ofMesh::sphere(10);
        for (int i = 0; i < p.getNumVertices(); i++) {
            p.addColor(ofFloatColor(0.1, 0.4, 4.0));
        }
        
    };
    void update(){
        
        for (int i = 0; i < num; i++) {
            
            ps[i].update(&ps);
        }
        
    };
    void draw(ofCamera &cam){
        
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        
        gbShader.begin();
        gbShader.setUniformMatrix4f("normalMatrix", normalMatrix);
        gbShader.setUniform1f("farClip", cam.getFarClip());
        gbShader.setUniform1f("nearClip", cam.getNearClip());
        
        for (auto part : ps) {
            ofPushMatrix();
            ofTranslate(part.pos);
            
            p.draw();
            ofPopMatrix();
        }
        
        gbShader.end();
        
        for (auto part : ps) {
            
            lShader.begin();
            lShader.setUniform3f("to", part.pos);
            lShader.setUniformMatrix4f("normalMatrix", normalMatrix);
            lShader.setUniform1f("farClip", cam.getFarClip());
            lShader.setUniform1f("nearClip", cam.getNearClip());
            part.lines.draw();
            lShader.end();
        }
        
    };
    
    
private:
    ofShader lShader;
    ofShader gbShader;
    
    ofVboMesh p;
    const unsigned num = 100;
    vector<Particle> ps;
    
    
    float thresh = 100.;
};

