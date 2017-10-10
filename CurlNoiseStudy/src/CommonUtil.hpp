#pragma once
#include "ofMain.h"

struct PingPongBuffer {
public:
    void allocate( int _width, int _height){
        
        for(int i = 0; i < 2; i++){
            
            ofFbo::Settings s;
            s.width = _width;
            s.height = _height;
            s.internalformat = GL_RGBA32F;
            s.numColorbuffers = 2;
            
            FBOs[i].allocate(s);
            FBOs[i].createAndAttachTexture(GL_RGBA32F, 1);
            FBOs[i].createAndAttachTexture(GL_RGBA32F, 2);
            
            FBOs[i].getTexture(0).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            FBOs[i].getTexture(1).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        }
        
        clear();
    }
    
    void swap(){
        std::swap(src,dst);
    }
    
    void clear(){
        for(int i = 0; i < 2; i++){
            FBOs[i].begin();
            ofClear(0,255);
            FBOs[i].end();
        }
    }
    
    ofFbo& operator[]( int n ){ return FBOs[n];}
    ofFbo *src = &FBOs[0];
    ofFbo *dst = &FBOs[1];
    
private:
    ofFbo FBOs[2];
};

