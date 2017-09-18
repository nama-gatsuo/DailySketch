#pragma once
#include "ofShader.h"

class WireFrameShader : public ofShader {
public:
    void setup(){
        setGeometryInputType(GL_TRIANGLES);
        setGeometryOutputType(GL_TRIANGLE_STRIP);
        setGeometryOutputCount(3);
        load("shader/scene/wireframe.vert",
             "shader/scene/wireframe.frag",
             "shader/scene/wireframe.geom");
    };
    void begin(ofCamera &cam, float wireWidth, bool isDrawFace, bool isShadow){
        ofShader::begin();
        setUniform1f("nearClip", cam.getNearClip());
        setUniform1f("farClip", cam.getFarClip());
        setUniform1f("wireWidth", wireWidth);
        setUniform1i("isDrawFace", isDrawFace?1:0);
        setUniform1i("isShadow", isShadow?1:0);
    };
    
};
