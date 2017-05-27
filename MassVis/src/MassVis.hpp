#pragma once
#include "ofMain.h"

class MassVis {
public:
    MassVis(){};
    void setup(string soundPath){
        
        for (int i = 0; i < 2; i++) {
            soundTex[i].allocate(fftSize, historySize, GL_R16);
            soundTex[i].begin();
            ofClear(0);
            soundTex[i].end();
        }
        
        updateShader.load("shader/scene/Update");
        
        mesh = ofMesh::box(5.0, 5.0, 5.0, 1, 1, 1);
        shader.load("shader/scene/MassVis");
        
        sound.load(soundPath);
        
    };
    
    void update(){
        ofSoundUpdate();
        float * val = ofSoundGetSpectrum(512);
        
        soundTex[current].begin();
        ofClear(0);
        
        updateShader.begin();
        updateShader.setUniform1i("ffSize", fftSize);

        updateShader.setUniform1fv("rawFft", val, fftSize);
        
        soundTex[1-current].draw(0,0);
        
        updateShader.end();
        soundTex[current].end();
        
        current = 1 - current;
    };
    
    void draw(ofCamera &cam){
        
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        cam.begin();
        
        shader.begin();
        shader.setUniformTexture("soundTex", soundTex[current].getTexture(), 1);
        shader.setUniformMatrix4f("normalMatrix", normalMatrix);
        shader.setUniform1f("farClip", cam.getFarClip());
        shader.setUniform1f("nearClip", cam.getNearClip());
        mesh.drawInstanced(OF_MESH_FILL, historySize * fftSize);
        shader.end();
        
        cam.end();
        
    };
    
    void play(){
        sound.play();
    }
    
    void debugDraw(){
        soundTex[0].draw(0,0, 256, 256);
        soundTex[1].draw(256,0, 256, 256);
        ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 10, 10);
    };
    
    
private:
    const int historySize = 256;
    const int fftSize = 256;
    
    int current = 0;
    ofFbo soundTex[2];
    ofShader updateShader;
    
    ofShader shader;
    ofVboMesh mesh;
    
    ofSoundPlayer sound;
};
