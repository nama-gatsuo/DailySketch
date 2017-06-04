// modified structure synth script of Orihaus
// https://www.flickr.com/photos/orihaus/7407230100

#include "ofMain.h"

class HexaStruct {
public:
    HexaStruct(){};
    void setup(){
        int num = 21;
        ofMatrix4x4 mat;
        mat.glScale(100, 100, 100);
        mat.glTranslate(-10, 0., 0.);
        mat.glRotate(90, 1., 0., 0.);
        
        ofFloatColor c(1.0,1.0,1.0,1.0);
        for (int i = 0; i < num; i++) {
            mat.glRotate(8, 1, 0, 0);
            mat.glRotate(6, 0, 1, 0);
            mat.glTranslate(1.0, 0, 0);
            panelStruct(mat, c);
        }
        
    };
    void draw(){
        mesh.draw();
    };
private:
    void panelStruct(ofMatrix4x4 mat, ofFloatColor c){
        mat.glRotate(90, 0, 1, 0);
        for (int i = 0; i < 6; i++){
            mat.glTranslate(0, 1.0, 0);
            mat.glRotate(-60, 0,0,1);
            mat.glTranslate(0, 1.0, 0);
            panel(mat, c);
        }
    };
    void panel(ofMatrix4x4 mat, ofFloatColor c){
        
        c.set(1.0,1.0,1.0,1.0);
        ofMatrix4x4 m = mat;
        m.glRotate(90, 0,0,1);
        m.glScale(0.2, 0.05, 0.1);
        beamAssembly(m, c);
        
        float coin = ofRandom(1.0);
        
        c.setHsb(0.51, 0.5, 0.3);
        if (coin < 0.8) {
            m = mat;
            m.glScale(0.05, 2.0, 0.8);
            box(m, c);
        }
        
    };
    void beamAssembly(ofMatrix4x4 mat, ofFloatColor c){
        float coin = ofRandom(1.0);
        
        if (coin < 0.8) {
            ofMatrix4x4 m = mat;
            m.glScale(1., 0.2, 11.);
            m.glTranslate(0, 12, 0);
            box(m, c);
            
            m = mat;
            m.glScale(1., 0.2, 11.);
            m.glTranslate(0, -12, 0);
            box(m, c);
            
            m = mat;
            m.glTranslate(0,0,0.4);
            vertPanel(m, c);
            
            m = mat;
            m.glTranslate(0,0,5.);
            vertPanel(m, c);
            
            m = mat;
            m.glTranslate(0,0,-5.);
            vertPanel(m, c);
        }
        
    };
    void vertPanel(ofMatrix4x4 mat, ofFloatColor c){
        float coin = ofRandom(1.0);
        ofMatrix4x4 m;
        
        if (coin < 0.3) {
            m = mat;
            m.glScale(1., 4., 0.2);
            box(m, c);
            
            m = mat;
            m.glScale(1., 1., 0.5);
            box(m, c);
        } else if (coin < 0.6) {
            m = mat;
            thinBeam(m, c);
            
            m.glTranslate(0, 5., 0);
            thinBeam(m, c);
            
            m = mat;
            m.glTranslate(4.9, 2.5, 0);
            thinBeamVert(m, c);
            
            m = mat;
            m.glTranslate(-4.9, 2.5, 0);
            thinBeamVert(m, c);
            
            m = mat;
            pane(m, c);
        } else {
            m = mat;
            m.glScale(1, 1, 0.5);
            box(m, c);
            
            m = mat;
            m.glScale(0.2, 4, 0.2);
            m.glTranslate(2, 0, 0);
            box(m, c);
            
            m = mat;
            m.glScale(0.2, 4, 0.2);
            m.glTranslate(-2, 0, 0);
            box(m, c);
            
            m = mat;
            m.glScale(1.0, 0.2, 0.2);
            m.glTranslate(0, 10., 0);
            box(m, c);
            
            m = mat;
            m.glScale(1.0, 0.2, 0.2);
            m.glTranslate(0, -10., 0);
            box(m, c);
        }
    };
    void thinBeam(ofMatrix4x4 mat, ofFloatColor c){
        mat.glScale(10, 0.2, 0.2);
        box(mat, c);
    };
    void thinBeamVert(ofMatrix4x4 mat, ofFloatColor c){
        mat.glScale(0.2, 5, 0.2);
        box(mat, c);
    }
    void pane(ofMatrix4x4 mat, ofFloatColor c){
        mat.glScale(10, 2.5, 0.05);
        mat.glTranslate(0, 0.5, 0);
        box(mat, c);
    };
    void box(ofMatrix4x4 mat, ofFloatColor c){
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
    ofVboMesh mesh;
};
