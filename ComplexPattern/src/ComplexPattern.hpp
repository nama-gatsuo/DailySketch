#include "ofMain.h"

class ComplexPattern {
public:
    ComplexPattern(){};
    void setup(){
        
        mesh.clear();
        
        ofMatrix4x4 m;
        m.glScale(200, 200, 200);
        m.glTranslate(0., -2., 0);
        for (int i = 0; i < 15; i++) {
            
            m.glRotate(11, 0, 1, 0);
            m.glScale(0.9, 0.9, 0.9);
            m.glTranslate(0,0.3,0);
            ring(m);
            
        }
        
    };
    
    void ring(ofMatrix4x4 _m){
        ofMatrix4x4 m = _m;
        
        for (int i = 0; i < 5; i++) {
            
            ofMatrix4x4 mm = m;
            mm.glRotate(72 * i, 0, 1, 0);
            mm.glTranslate(1,0,0);
            mm.glRotate(90,0,1,0);
            petal(mm);
            
        }
    }
    
    void petal(ofMatrix4x4 _m){
        
        ofMatrix4x4 m = _m;
        m.glRotate(80, 1, 0, 0);
        for (int i = 0; i < 9; i++) {
            m.glRotate(-6, 1, 0, 0);
            m.glTranslate(0, 1, 0);
            pane(m);
        }
        
        m = _m;
        m.glRotate(80, 1, 0, 0);
        m.glRotate(-25, 0, 0, 1);
        for (int i = 0; i < 9; i++) {
            m.glRotate(4, 0, 0, 1);
            m.glRotate(-6, 1, 0, 0);
            m.glTranslate(0, 1, 0);
            pane(m);
        }
        
        m = _m;
        m.glRotate(80, 1, 0, 0);
        m.glRotate(25, 0, 0, 1);
        for (int i = 0; i < 9; i++) {
            m.glRotate(-4, 0, 0, 1);
            m.glRotate(-6, 1, 0, 0);
            m.glTranslate(0, 1, 0);
            pane(m);
        }
    };
    
    void pane(ofMatrix4x4 _m){
        
        ofMatrix4x4 m = _m;
        ofFloatColor c(0.1, 0.1, 0.1);
        
        float coin = ofRandom(1.);
        if (coin < 0.3) {
            m.glScale(1.,1.,0.05);
            addBox(m, c);
            
            coin = ofRandom(1.);
            if (coin < 0.5) {
                m.glScale(0.8,0.8,2.);
                addBox(m, c);
            }
        }
        
        m = _m;
        coin = ofRandom(1.);
        if (coin < 0.9) {
            beam(m);
        }
        
    }
    
    void beam(ofMatrix4x4 _m){
        
        ofFloatColor c(1.);
        ofFloatColor bc(0.1);
        ofFloatColor lc(1.5, 0.8, 1.2);
        
        // vertical
        ofMatrix4x4 m = _m;
        m.glTranslate(0, 0, -0.2);
        m.glScale(0.05, 1, 0.05);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0, 0, 0.2);
        m.glScale(0.05, 1, 0.05);
        addBox(m, c);
        
        m = _m;
        m.glScale(0.05, 0.05, 0.4);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0, 0.5, 0);
        m.glScale(0.05, 0.05, 0.4);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0, 0.5, 0);
        m.glScale(0.05, 0.05, 0.4);
        addBox(m, c);
        
        
        // horizontal
        float coin = ofRandom(1.);
        if (coin < 0.1) {
            m = _m;
            m.glScale(1., 0.01, 0.3);
            addBox(m, bc);
            
            m = _m;
            m.glTranslate(0, 0, -0.22);
            m.glScale(1., 0.05, 0.05);
            addBox(m, lc);
            
            m = _m;
            m.glTranslate(0, 0, 0.22);
            m.glScale(1., 0.03, 0.05);
            addBox(m, c);
            
            m = _m;
            m.glTranslate(0, 0.03, 0);
            m.glScale(0.05, 0.05, 0.4);
            addBox(m, c);
        }
        
    };
    
    void addBox(ofMatrix4x4& _m, ofFloatColor& _c){
        
        ofMesh box = ofMesh::box(1,1,1, 1,1,1);
        for (int i = 0; i < box.getNumVertices(); i++) {
            
            ofVec3f v = box.getVertex(i) * _m;
            ofVec3f n = ((box.getNormal(i) + box.getVertex(i)) * _m - v).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            box.addColor(_c);
        }
        
        mesh.append(box);
        
    };
    
    void draw(){
        
        mesh.draw();
        
    };
private:
    ofVboMesh mesh;
    
    
};
