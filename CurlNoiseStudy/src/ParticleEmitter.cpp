#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter():pos(0.),radius(100.),noiseScale(10.),noiseStrength(1.),pointSize(10.) {
    
}

void ParticleEmitter::setup(){
    
    render.load("shader/scene/render");
    updateData.load("shader/scene/passThru.vert", "shader/scene/updateData.frag");
    createData.load("shader/scene/passThru.vert", "shader/scene/createData.frag");
    
    const int wNum = 1024, hNum = 1024;
    
    pingPong.allocate(wNum, hNum);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for (int x = 0; x < wNum; x++) {
        
        for (int y = 0; y < hNum; y++) {
            ofVec3f v = ofVec3f();
            mesh.addVertex(v);
            mesh.addTexCoord(ofVec2f(x, y));
        }
        
    }
    
    ofFbo::Settings s;
    s.width = wNum;
    s.height = hNum;
    s.internalformat = GL_RGBA32F;
    s.numColorbuffers = 2;
    startData.allocate(s);
    startData.createAndAttachTexture(GL_RGBA32F, 1);
    startData.createAndAttachTexture(GL_RGBA32F, 2);
    startData.getTexture(0).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    startData.getTexture(1).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    createData.begin();
    createData.setUniform2f("texRes", wNum, hNum);
    createData.end();
    createStartPos();
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ParticleEmitter::update(){
    pingPong.dst->begin();
    pingPong.dst->activateAllDrawBuffers();
    ofClear(0);
    
    updateData.begin();
    updateData.setUniform3f("pos", pos);
    updateData.setUniform3f("prevPos", prevPos);
    updateData.setUniformTexture("startPosAndAge", startData.getTexture(0), 1);
    updateData.setUniformTexture("startVel", startData.getTexture(1), 2);
    updateData.setUniformTexture("currentPosAndAge", pingPong.src->getTexture(0), 3);
    updateData.setUniformTexture("currentVel", pingPong.src->getTexture(1), 4);
    updateData.setUniform1f("turbulence", turbulence);
    updateData.setUniform1f("noiseStrength", noiseStrength);
    updateData.setUniform1f("noiseScale", noiseScale);
    
    pingPong.src->draw(0, 0);
    
    updateData.end();
    pingPong.dst->end();
    
    pingPong.swap();
}

void ParticleEmitter::draw(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    render.begin();
    render.setUniformTexture("currentDataTex", pingPong.dst->getTexture(0), 1);
    render.setUniformTexture("startDataTex", startData.getTexture(0), 2);
    render.setUniform4f("toColor", toColor);
    render.setUniform4f("fromColor", fromColor);
    render.setUniform1f("pointSize", pointSize);
    mesh.draw();
    render.end();
    
    ofDisableBlendMode();
}

void ParticleEmitter::setPosition(const ofVec3f& pos){
    ParticleEmitter::prevPos = ParticleEmitter::pos;
    ParticleEmitter::pos = pos;
}

void ParticleEmitter::createStartPos(){
    
    startData.begin();
    startData.activateAllDrawBuffers();
    
    ofClear(0);
    createData.begin();
//    createData.setUniform3f("pos", pos);
//    createData.setUniform3f("prevPos", prevPos);
    createData.setUniform1f("radius", radius);
    createData.setUniform1f("maxLife", 200);
    startData.draw(0, 0);
    createData.end();
    
    startData.end();
}

void ParticleEmitter::debugDraw(){
    pingPong.src->getTexture(0).draw(0,0);
    startData.getTexture(0).draw(256,0);
};
