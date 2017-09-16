#include "ofMain.h"

class Arc {
public:
    Arc(){
        startDelay = floor(ofRandom(40));
        startAngle = PI * ofRandom(1.5);
        SA = startAngle;
        angle = PI * ofRandom(0.5, 1.);
        radius = 30 + 200 * ofRandom(1.);
        morpDuration = 10;
        stayDuration = 30;
    };
    void update(){
        t++;
        
        if (t == startDelay) mode = 1;
        if (t == startDelay + morpDuration) mode = 2;
        if (t == startDelay + morpDuration + stayDuration) mode = 3;
        if (t == startDelay + morpDuration * 2 + stayDuration) mode = 4;
        
        switch (mode) {
            case 0:
                endAngle = startAngle;
                break;
            case 1:
                endAngle = startAngle + angle * sin(HALF_PI * (t - startDelay) / morpDuration);
                break;
            case 2: break;
            case 3:
                startAngle = SA + angle * sin(HALF_PI * (t - (startDelay+morpDuration+stayDuration)) / morpDuration);
                break;
            case 4: break;
            default: break;
        }
        
    };
    
    bool isDead(){
        return mode == 4;
    };
    
    float radius;
    float angle;
    float startAngle, endAngle;
    int startDelay;
    int stayDuration, morpDuration;
    int t = 0;
    int mode = 0;
    float SA;
};

class Line {
public:
    Line(){
        
        angle = TWO_PI * ofRandom(1.);
        r1 = 50 + 50 * ofRandom(1.);
        dist = 50 + 120 * ofRandom(1.);
        SR = r1;
        
        startDelay = floor(ofRandom(40));
        morpDuration = 10;
        stayDuration = 30;
    };
    void update(){
        t++;
        
        if (t == startDelay) mode = 1;
        if (t == startDelay + morpDuration) mode = 2;
        if (t == startDelay + morpDuration + stayDuration) mode = 3;
        if (t == startDelay + morpDuration * 2 + stayDuration) mode = 4;
        
        switch (mode) {
            case 0:
                r2 = r1;
                break;
            case 1:
                r2 = SR + dist * sin(HALF_PI * (t - startDelay) / morpDuration);
                break;
            case 2: break;
            case 3:
                r1 = SR + dist * sin(HALF_PI * (t - (startDelay+morpDuration+stayDuration)) / morpDuration);
                break;
            case 4: break;
            default: break;
        }
        
    };
    bool isDead(){
        return mode == 4;
    };
    
    float r1, r2, dist;
    float SR;
    float angle;
    int startDelay;
    int stayDuration, morpDuration;
    int t = 0;
    int mode = 0;
};

class CyberCrater {
public:
    CyberCrater(ofShader &ls, ofShader &as){
        center = ofVec3f(ofRandom(-1,1) * 500., ofRandom(-1,1)*300, ofRandom(-1,1) * 500.);
        
        lineShader = ls;
        arcShader = as;
        for (int i = 0; i < 30; i++) {
            arcs.push_back( Arc() );
        }
        
        for (int i = 0; i < 15; i++) {
            lines.push_back( Line() );
        }
        
        mesh = ofMesh::box(1., 1., 1., 1, 1, 1);
    
    };
    void update(){
        vector<Arc>::iterator it;
        for (it = arcs.begin(); it < arcs.end(); it++) {
            it->update();
            if (it->isDead()) arcs.erase(it);
        }
        
        vector<Line>::iterator itl;
        for (itl = lines.begin(); itl < lines.end(); itl++) {
            itl->update();
            if (itl->isDead()) lines.erase(itl);
        }
    };
    void draw(ofCamera &cam, bool isShadow){
        
        ofPushMatrix();
        ofTranslate(center);
        
        for (auto arc : arcs) {
            arcShader.begin();
            arcShader.setUniform1i("isShadow", isShadow?1:0);
            arcShader.setUniform1i("total", 20);
            arcShader.setUniform1f("radius", arc.radius);
            arcShader.setUniform1f("startAngle", arc.startAngle);
            arcShader.setUniform1f("endAngle", arc.endAngle);
            arcShader.setUniform1f("nearClip", cam.getNearClip());
            arcShader.setUniform1f("farClip", cam.getFarClip());
            
            mesh.drawInstanced(OF_MESH_FILL, 20);
            
            arcShader.end();
        }
        
        for (auto line : lines) {
            lineShader.begin();
            lineShader.setUniform1i("isShadow", isShadow?1:0);
            lineShader.setUniform1f("angle", line.angle);
            lineShader.setUniform1f("r1", line.r1);
            lineShader.setUniform1f("r2", line.r2);
            lineShader.setUniform1f("nearClip", cam.getNearClip());
            lineShader.setUniform1f("farClip", cam.getFarClip());
            
            mesh.draw();
            
            lineShader.end();
        }
        
        ofPopMatrix();
    };
    bool isDead(){
        return arcs.size() == 0;
    }
    
private:
    ofShader lineShader;
    ofShader arcShader;
    vector<Arc> arcs;
    vector<Line> lines;
    ofVec3f center;
    ofVboMesh mesh;
};
