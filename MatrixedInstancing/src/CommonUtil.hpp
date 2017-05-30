#pragma once
#include "ofMain.h"

class SmoothPoint : public ofPoint{
public:
    SmoothPoint():mSpeed(0.01){};
    void update(){
        this->x += (mTarget.x - this->x) * mSpeed;
        this->y += (mTarget.y - this->y) * mSpeed;
        this->z += (mTarget.z - this->z) * mSpeed;
    }
    void to(ofPoint target){
        mTarget = target;
    }
    void setSpeed(float speed){
        mSpeed = speed;
    }
    
private:
    ofPoint mTarget;
    float mSpeed;
};
