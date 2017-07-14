#include "FractalInstancing.hpp"

using namespace FractInst;

void Tree::setup(){
    shader.load("shader/scene/shader");
    
    for (int i = 0; i < depth; i++) {
        num.push_back(pow(6., i));
    }
    
    mesh = ofMesh::box(1.,1.,1., 1,1,1);
    
    ofFloatColor col;
    col.set(0.4, 0.8, 0.9);
    
    for (int i = 0; i < mesh.getNumIndices(); i++){
        mesh.addColor(col);
    }
    
    scale.assign(depth, SmoothValue());
    translate.assign(depth, SmoothValue());
    
}

void Tree::update(){
    
    boxSize.update();
    
    for (int i = 0; i < depth; i++) {
        
        scale[i].update();
        translate[i].update();
        
    }
    
}

void Tree::draw(ofCamera cam, bool isShadow){
    
    ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
    
    shader.begin();
    shader.setUniform1i("isShadow", isShadow?1:0);
    shader.setUniformMatrix4f("normalMatrix", normalMatrix);
    shader.setUniform1f("farClip", cam.getFarClip());
    shader.setUniform1f("nearClip", cam.getNearClip());
    
    vector<float> sca;
    vector<float> tra;

    shader.end();
    
    for (int i = 0; i < depth; i++) {
        sca.clear();
        tra.clear();
        
        for (int j = 0; j < depth; j++) {
            if (i > j) {
                sca.push_back(scale[j].getValue());
                tra.push_back(translate[j].getValue());
            } else {
                sca.push_back(1.);
                tra.push_back(0.);
            }
        }
        
        shader.begin();
        shader.setUniform3f("boxSize", boxSize);
        shader.setUniform1i("division", division);
        shader.setUniform1fv("dscale", sca.data(), depth);
        shader.setUniform1fv("translate", tra.data(), depth);
        shader.setUniform1i("index", i);
        mesh.drawInstanced(OF_MESH_FILL, num[i]);
        shader.end();
    }
}

void Tree::randomize(){
    
    float coin = ofRandom(1.0);
    
    if (coin < 0.33) boxSize.to(ofPoint(0.5,0.5, ofRandom(20.)));
    else if (coin < 0.66) boxSize.to(ofPoint(ofRandom(20.), 0.5,0.5));
    else boxSize.to(ofPoint(0.5, ofRandom(20.), 0.5));
    
    division = floor(ofRandom(3.0, 7.));
    
    for (int i = 0; i < depth; i++) {
        
        scale[i].to(ofRandom(0.5, 1.));
        translate[i].to(ofRandom(5, 10.));
        
    }
}
