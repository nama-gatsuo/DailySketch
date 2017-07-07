#include "ofMain.h"

class CalatravaStruct {
public:
    void setup();
    void update();
    void draw(ofCamera cam, bool isShadow);
    
    ofParameterGroup params;
    ofParameter<ofVec3f> fromTrans, fromRotate, fromScale;
    ofParameter<ofVec3f> toTrans, toRotate, toScale;
    
private:
    ofVboMesh mesh;
    ofShader shader;
    
    int num = 200;
    
};
