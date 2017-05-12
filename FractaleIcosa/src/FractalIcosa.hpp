#include "ofMain.h"

class FractalIcosa {
public:
    void setup(){
        createMesh();
    };
    void update(){};
    void draw(){
        mesh.draw();
    };
    
    void createMesh(){
        float t = (1.0 + sqrt(5)) / 2;
        
        ofVec3f verts[12] = {
            ofVec3f(-1, t,  0), ofVec3f(1, t, 0), ofVec3f(-1, -t, 0), ofVec3f(1, -t,  0),
            ofVec3f(0, -1,  t), ofVec3f(0, 1, t), ofVec3f(0, -1, -t), ofVec3f(0,  1, -t),
            ofVec3f(t,  0, -1), ofVec3f(t, 0, 1), ofVec3f(-t, 0, -1), ofVec3f(-t, 0,  1)
        };
        int faces[60] = {
            0, 11,  5,    0,  5,  1,    0,  1,  7,    0,  7, 10,    0, 10, 11,
            1,  5,  9,    5, 11,  4,   11, 10,  2,   10,  7,  6,    7,  1,  8,
            3,  9,  4,    3,  4,  2,    3,  2,  6,    3,  6,  8,    3,  8,  9,
            4,  9,  5,    2,  4, 11,    6,  2, 10,    8,  6,  7,    9,  8,  1
        };
        
        float edge = (verts[0] - verts[11]).length();
        
        ofVec3f v[3];
        ofFloatColor c;
        c.setHsb(0.65, 0.2, 0.9);
        for (int i = 0; i < 60; i += 3) {
            v[0] = verts[faces[i]] * 100;
            v[1] = verts[faces[i + 1]] * 100;
            v[2] = verts[faces[i + 2]] * 100;
            
            ofVec3f n = (v[2] - v[0]).cross(v[1] - v[0]);
            mesh.addVertex(v[0]);
            mesh.addVertex(v[1]);
            mesh.addVertex(v[2]);
            mesh.addNormal(n);
            mesh.addNormal(n);
            mesh.addNormal(n);
            mesh.addColor(c);
            mesh.addColor(c);
            mesh.addColor(c);
            
            createFace(v, 0);
            
        }
        
        
    };
    void createFace(ofVec3f * v, int level){
        
        if (level == 5) return;
        float sign = pow(-1.0, level);
        ofVec3f _v[3];
        float r1 = 0.5;
        float r2 = 0.0;
        _v[0] = v[0].getInterpolated(v[1], r1).getInterpolated(v[2], r2);
        _v[1] = v[1].getInterpolated(v[2], r1).getInterpolated(v[0], r2);
        _v[2] = v[2].getInterpolated(v[0], r1).getInterpolated(v[1], r2);
        
        float edge = (_v[0] - _v[1]).length();
        float perp = edge * pe;
        ofVec3f vperp = (_v[0] - _v[2]).cross(_v[1] - _v[2]).normalize() * perp * sign;
        vperp = vperp + (_v[0] + _v[1] + _v[2]) / 3.0;
        
        level += 1;
        
        ofVec3f _tv[3];
        ofFloatColor c;
        c.setHsb(0.4 + 0.25 * sign, 0.2, 0.9);
        
        for (int i = 0; i < 3; i++) {
            int i1 = i;
            int i2 = i == 2 ? 0 : i+1;
            ofVec3f n = (_v[i2] - vperp).cross(_v[i1] - vperp) * sign;
            mesh.addVertex(_v[i2]);
            mesh.addVertex(_v[i1]);
            mesh.addVertex(vperp);
            mesh.addNormal(n);
            mesh.addNormal(n);
            mesh.addNormal(n);
            mesh.addColor(c);
            mesh.addColor(c);
            mesh.addColor(c);
            
            _tv[0] = _v[i1];
            _tv[1] = _v[i2];
            _tv[2] = v[i2];
            createFace(_tv, level);
            
            _tv[0] = _v[i2];
            _tv[1] = _v[i1];
            _tv[2] = vperp;
            createFace(_tv, level);
            
        }
        
    };

private:
    ofVboMesh mesh;
//    const float pe = 0.816497;
    float pe = 1.63;
};
