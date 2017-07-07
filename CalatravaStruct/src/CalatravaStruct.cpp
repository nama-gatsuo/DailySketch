#include "CalatravaStruct.hpp"

void CalatravaStruct::setup(){
    shader.load("shader/scene/shader");
    shader.begin();
    shader.setUniform1i("total", num);
    shader.end();
    
    mesh = ofMesh::box(1.,1.,1., 1,1,1);
    
    ofFloatColor col;
    col.set(1.);
    
    for (int i = 0; i < mesh.getNumIndices(); i++){
        mesh.addColor(col);
    }
    
    params.setName("object_parameters");
    params.add(fromTrans.set("translate_from", ofVec3f(0.), ofVec3f(0.), ofVec3f(100.)));
    params.add(toTrans.set("translate_to", ofVec3f(0.), ofVec3f(0.), ofVec3f(100.)));
    params.add(fromRotate.set("rotate_from", ofVec3f(0.), ofVec3f(0.), ofVec3f(TWO_PI*2.)));
    params.add(toRotate.set("rotate_to", ofVec3f(0.), ofVec3f(), ofVec3f(TWO_PI*2.)));
    params.add(fromScale.set("scale_from", ofVec3f(0.1), ofVec3f(0.), ofVec3f(20.)));
    params.add(toScale.set("scale_to", ofVec3f(0.1), ofVec3f(0.), ofVec3f(20.)));
    
}

void CalatravaStruct::update(){
    
}

void CalatravaStruct::draw(ofCamera cam, bool isShadow){
    
    ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
    
    shader.begin();
    shader.setUniform1i("isShadow", isShadow?1:0);
    shader.setUniformMatrix4f("normalMatrix", normalMatrix);
    shader.setUniform1f("farClip", cam.getFarClip());
    shader.setUniform1f("nearClip", cam.getNearClip());
    
    shader.setUniform3f("fromTrans", fromTrans);
    shader.setUniform3f("fromRotate", fromRotate);
    shader.setUniform3f("fromScale", fromScale);
    shader.setUniform3f("toTrans", toTrans);
    shader.setUniform3f("toRotate", toRotate);
    shader.setUniform3f("toScale", toScale);
    
    mesh.drawInstanced(OF_MESH_FILL, num);
    
    shader.end();
}
