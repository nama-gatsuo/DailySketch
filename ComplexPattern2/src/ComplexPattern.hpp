#include "ofMain.h"

class ComplexPattern {
public:
    ComplexPattern(){};
    void setup(){
        
        mesh.clear();
        
        ofMatrix4x4 m;
        m.glScale(200, 200, 200);
        
        int nt = 36;
        int nt_offset = 0;
        int ns = 24;
        int ns_offset = 4;
        
        for (int i = nt_offset; i <= nt-nt_offset; i++) {
            
            for (int j = ns_offset+1; j <= ns - ns_offset; j++) {
                
                ofMatrix4x4 _m = m;
                _m.glRotate(360 / nt * i, 0,1,0);
                _m.glRotate(180 / ns * j -90, 0,0,1);
                _m.glTranslate(6, 0, 0);
                
                structure(_m);
                
            }
            
        }
        
    };
    
    void structure(ofMatrix4x4 _m){
        
        ofMatrix4x4 m = _m;
        m.glRotate(-90, 0,0,1);
        
        float coin = ofRandom(1.);
        if (coin < .5) {
            tower(m);
        } else {
            pipe(m);
        }
        
    }
    
    void tower(ofMatrix4x4 _m){
        ofMatrix4x4 m = _m;
        ofFloatColor c(0.1);
        
        for (int i = 0; i < 16; i++) {
            if (ofRandom(1.) < 0.4) {
                m.glScale(1.2, 1.2, 1.2);
            } else {
                m.glScale(0.8, 0.8, .8);
            }
            
            for (int j = 0; j < 2; j++){
                for (int k = 0; k < 2; k++){
                    ofMatrix4x4 __m = m;
                    __m.glTranslate(0.25 + 0.5*j, 0., 0.25 + 0.5 * k);
                    if (ofRandom(1.) < 0.5) {
                        __m.glScale(0.5,0.5,0.5);
                        beam(__m);
                    } else {
                        if (ofRandom(1.) < 0.4) {
                            __m.glScale(0.3, 0.2, 0.3);
                        } else {
                            __m.glScale(0.4, 0.35, 0.4);
                        }
                        addBox(__m, c);
                    }
                }
            }
            if (ofRandom(1.) < 0.4) {
                m.glTranslate(0., .4, 0.);
            } else {
                m.glTranslate(0., .1, 0.);
            }
            
            
            if (ofRandom(1.) < 0.2) {
                return;
            }
        }
    }
    
    void pipe(ofMatrix4x4 _m){
        
        ofFloatColor c(0.1);
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                ofMatrix4x4 m = _m;
                m.glTranslate(0.25 + 0.5*j, 0., 0.25 + 0.5 * k);
                if (ofRandom(1.) < 0.4) {
                    m.glRotate(90, 1, 0, 0);
                    beam(m);
                } else {
                    if (ofRandom(1.) < 0.4) {
                        m.glScale(0.4, 0.01, 0.4);
                    } else {
                        m.glScale(0.6, 0.01, 0.6);
                    }
                    
                    addBox(m, c);
                }
            }
        }
        
    };
    
    
    
    void beam(ofMatrix4x4 _m){
        
        ofFloatColor c(1.);
        ofFloatColor bc(0.1);
        
        // vertical
        ofMatrix4x4 m = _m;
        m.glTranslate(0, 0, -0.05);
        m.glScale(0.06, 1, 0.02);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0, 0, 0.05);
        m.glScale(0.06, 1, 0.02);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0, 0.5, 0);
        m.glScale(0.06, 0.01, 0.1);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(-0.05, 0, 0);
        m.glScale(0.02, 0.4, 0.1);
        addBox(m, c);
        
        m = _m;
        m.glTranslate(0.05, 0, 0);
        m.glScale(0.02, 0.4, 0.1);
        addBox(m, c);
        
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
