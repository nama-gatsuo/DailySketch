#pragma once
#include "ofMain.h"
#include "CommonUtil.hpp"

class MatInst {
public:
    MatInst(){};
    void setup(){
        createMesh();
        shader.load("shader/scene/MatInst");
        shader.begin();
        shader.setUniform2f("size", xSize, ySize);
        shader.end();
    };
    void update(){
        rot1.update();
        scale1.update();
        trans1.update();
        rot2.update();
        scale2.update();
        trans2.update();
    };
    void draw(ofCamera &cam){
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        
        shader.begin();
        shader.setUniformMatrix4f("normalMatrix", normalMatrix);
        shader.setUniform1f("farClip", cam.getFarClip());
        shader.setUniform1f("nearClip", cam.getNearClip());
        
        shader.setUniform3f("rot1", rot1);
        shader.setUniform3f("scale1", scale1);
        shader.setUniform3f("trans1", trans1);
        shader.setUniform3f("rot2", rot2);
        shader.setUniform3f("scale2", scale2);
        shader.setUniform3f("trans2", trans2);
        mesh.drawInstanced(OF_MESH_FILL, xSize * ySize);
        shader.end();
    };
    void randomize(){
        float tfactor = 300;
        float sMin = 0.0;
        float sMax = 4.0;
        float rMin = TWO_PI*1.0;
        float rMax = TWO_PI*2.0;
        
        rot1.to(ofPoint(ofRandom(rMin, rMax), ofRandom(rMin, rMax), ofRandom(rMin, rMax)));
        scale1.to(ofPoint(ofRandom(sMin, sMax), ofRandom(sMin, sMax), ofRandom(sMin, sMax)));
        trans1.to(ofPoint(ofRandom(1.0)*tfactor, ofRandom(1.0)*tfactor, ofRandom(1.0)*tfactor));
        rot2.to(ofPoint(ofRandom(rMin, rMax), ofRandom(rMin, rMax), ofRandom(rMin, rMax)));
        scale2.to(ofPoint(ofRandom(sMin, sMax), ofRandom(sMin, sMax), ofRandom(sMin, sMax)));
        trans2.to(ofPoint(ofRandom(1.0)*tfactor, ofRandom(1.0)*tfactor, ofRandom(1.0)*tfactor));
    };
private:
    void createMesh(){
        
        ofFloatColor c1(0.9, 1.1, 1.2);
//        c1.setHsb(1.0, 1.0, 1.0);
        ofFloatColor c2;
        c2.setHsb(0.5, 0.5, 1.0);
        
        float w = 10.0;
        float h = 10.0;
        float d = 10.0;
        
        float t = 0.4;
        w += t;
        h += t;
        d += t;
        
        ofMatrix4x4 m;
        m.makeIdentityMatrix();
        m.glTranslate(w/2, h/2, 0);
        m.glScale(t, t, d);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(-w/2, h/2, 0);
        m.glScale(t, t, d);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(0, h/2, d/2);
        m.glScale(w, t, t);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(0, h/2, -d/2);
        m.glScale(w, t, t);
        createBox(m, c1);
        
        //
        m.makeIdentityMatrix();
        m.glTranslate(w/2, 0, d/2);
        m.glScale(t, h, t);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(w/2, 0, -d/2);
        m.glScale(t, h, t);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(-w/2, 0, -d/2);
        m.glScale(t, h, t);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(-w/2, 0, d/2);
        m.glScale(t, h, t);
        createBox(m, c1);
        
        //
        m.makeIdentityMatrix();
        m.glTranslate(w/2, -h/2, 0);
        m.glScale(t, t, d);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(-w/2, -h/2, 0);
        m.glScale(t, t, d);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(0, -h/2, d/2);
        m.glScale(w, t, t);
        createBox(m, c1);
        
        m.makeIdentityMatrix();
        m.glTranslate(0, -h/2, -d/2);
        m.glScale(w, t, t);
        createBox(m, c1);
        
        //
        m.makeIdentityMatrix();
        m.glRotate(45, 1,0,0);
        m.glRotate(45, 0,1,0);
        m.glRotate(45, 0,0,1);
        m.glScale(w * 0.8, h * 0.8, d * 0.8);
        createBox(m, c2);
        
        
    };
    void createBox(const ofMatrix4x4& mat, const ofFloatColor& c){
        ofMesh box = ofMesh::box(1.0, 1.0, 1.0, 1, 1, 1);
        
        for (int i = 0; i < box.getNumVertices(); i++) {
            ofVec3f v = box.getVertex(i) * mat;
            ofVec3f n = ((box.getNormal(i) + v) * mat - (v * mat)).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            box.addColor(ofFloatColor(c.r, c.g, c.b));
        }
        mesh.append(box);
    };
    
    const int xSize = 64;
    const int ySize = 64;
    
    ofVboMesh mesh;
    ofShader shader;
    
    SmoothPoint rot1;
    SmoothPoint rot2;
    SmoothPoint scale1;
    SmoothPoint scale2;
    SmoothPoint trans1;
    SmoothPoint trans2;
};
