#pragma once
#include "ofMain.h"

#include "ofxJSON.h"

struct CountryData{
    string id;
    vector<ofPath> pathes;
};

class MapCreator{
public:
    MapCreator();
    void setup();
    void setLayer();
    void draw(int x=0, int y=0);
    void draw(int x, int y, int w, int h);
    
private:
    vector<ofPath> createPath(ofXml &svg, ofVec2f& start);
    ofPath stringToPath(string &s, ofVec2f& start);
    ofVec2f stringToVec2(string &s);
    ofVec2f getLastPoint(ofPath &path);
    
    int w, h;
    ofVboMesh mesh;
    ofShader shader;
    ofFbo fbo;
    vector<CountryData> countries;
    
    ofxJSONElement json;
};
