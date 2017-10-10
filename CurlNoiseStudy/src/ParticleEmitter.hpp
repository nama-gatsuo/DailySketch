#pragma once
#include "ofMain.h"
#include "CommonUtil.hpp"

class ParticleEmitter {
public:
    ParticleEmitter();
    void setup();
    void update();
    void draw();
    
    void createStartPos();
    
    // setter
    void setPosition(const ofVec3f& pos);
    void setRadius(float radius){ ParticleEmitter::radius = radius; };
    void setFromColor(const ofFloatColor& color){ ParticleEmitter::fromColor = color; };
    void setToColor(const ofFloatColor& color){ ParticleEmitter::toColor = color; };
    void setPointSize(float pointSize){ ParticleEmitter::pointSize = pointSize; };
    void setNoiseScale(float scale){ noiseScale = scale; };
    void setNoiseStrength(float strength){ noiseStrength = strength; };
    void setTurbulence(float turbulence){ ParticleEmitter::turbulence = turbulence; };
    
    void debugDraw();
    
private:
    float pointSize;
    float radius;
    float noiseScale;
    float noiseStrength;
    float turbulence;
    int maxAge;
    
    ofVec3f pos = ofVec3f(0.), prevPos = ofVec3f(0.);
    ofFloatColor fromColor = ofFloatColor(1.), toColor = ofFloatColor(0.);
    
    // 0: (rgb)current position , (a)current age
    // 1: (rgb)current velocity
    PingPongBuffer pingPong;
    // 0: (rgb)start position , (a)max age
    // 1: (rgb)start velocity
    ofFbo startData;
    
    ofShader createData;
    ofShader updateData;
    ofShader render;
    
    ofVboMesh mesh;
    
    enum Mode { SPHERE = 0, SQUARE, POINT } mode;
};
