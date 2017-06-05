// modified structure synth script of Orihaus
// https://www.flickr.com/photos/orihaus/7406609466/

#include "ofMain.h"

class HexaSphere {
public:
    HexaSphere(){};
    void setup(){
        int num = 30;
        ofMatrix4x4 mat;
        mat.glTranslate(0, 200, 0);
        mat.glScale(20,20,20);
        
        ofFloatColor c(1.0,1.0,1.0,1.0);
        
        for (int i = 0; i < num; i++) {
            ofMatrix4x4 m = mat;
            m.glRotate(4, 1, 0, 0);
            m.glTranslate(0, 1.625, 0);
            dbox(m, c);
            
            m = mat;
            m.glRotate(-4, 1, 0, 0);
            m.glTranslate(2.25, -1.625, 0);
            m.glRotate(8, 0, 1, 0);
            ubox(m, c);
            
            mat.glTranslate(4.5, 0, 0);
            mat.glRotate(12, 0, 1, 0);
        }
        
        mat.makeIdentityMatrix();
        mat.glTranslate(0, 400, 0);
        mat.glRotate(180, 0, 0, 1);
        mat.glScale(20,20,20);
        
        for (int i = 0; i < num; i++) {
            ofMatrix4x4 m = mat;
            m.glRotate(4, 1, 0, 0);
            m.glTranslate(0, 1.625, 0);
            dbox(m, c);
            
            m = mat;
            m.glRotate(-4, 1, 0, 0);
            m.glTranslate(2.25, -1.625, 0);
            m.glRotate(8, 0, 1, 0);
            ubox(m, c);
            
            mat.glTranslate(4.5, 0, 0);
            mat.glRotate(12, 0, 1, 0);
        }
    };
    void draw(){
        mesh.draw();
    };
private:
    void dbox(ofMatrix4x4 mat, ofFloatColor c){
        
        for (int i = 0; i < 2; i++) {
            float coin = ofRandom(1.0);
            if (coin > 0.9) return;
            
            ofMatrix4x4 m = mat;
            m.glRotate(8, 1, 0, 0);
            hex2(m, c);
            
            mat.glRotate(-8, 1, 0, 0);
            mat.glTranslate(2.25, 3.25, 0);
            mat.glRotate(8, 0, 1, 0);
        }
    };
    void ubox(ofMatrix4x4 mat, ofFloatColor c){
        for (int i = 0; i < 2; i++) {
            float coin = ofRandom(1.0);
            if (coin > 0.9) return;
            
            ofMatrix4x4 m = mat;
            m.glRotate(8, 1, 0, 0);
            hex(m, c);
            
            mat.glRotate(8, 1, 0, 0);
            mat.glTranslate(2.25, -3.25, 0);
            mat.glRotate(8, 0, 1, 0);
        }
    };
    
    void hex2(ofMatrix4x4 mat, ofFloatColor c){
        for (int i = 0; i < 8; i++) {
            float coin = ofRandom(1.0);
            if (coin > 0.8) return;
            
            panel(mat, c);
            mat.glTranslate(0, 0, 1);
        }
    };
    void hex(ofMatrix4x4 mat, ofFloatColor c){
        for (int i = 0; i < 7; i++) {
            float coin = ofRandom(1.0);
            if (coin > 0.8) return;
            
            
            mat.glTranslate(0, 0, 1);
            panel(mat, c);
        }
    };
    
    
    void panel(ofMatrix4x4 mat, ofFloatColor c){
        
        for (int i = 0; i < 6; i++) {
            
            panelPart(mat, c);
            mat.glTranslate(0, 1.0, 0);
            mat.glRotate(-60, 0, 0, 1);
            mat.glTranslate(0, 1.0, 0);
            
        }
        
    };
    
    void panelPart(ofMatrix4x4 mat, ofFloatColor c){
        ofMatrix4x4 m = mat;
        m.glRotate(90, 0,0,1);
        m.glScale(0.2, 0.2, 0.1);
        beamAssembly(m, c);
        
        m = mat;
        m.glScale(0.1, 1.75, 1.);
        ofFloatColor c1;
        c1.setHsb(0.57, 0.4, 0.3);
        box(m, c1);
        
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
