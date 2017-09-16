#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setupDeferred();
    arcShader.load("shader/scene/arc.vert", "shader/scene/output.frag");
    lineShader.load("shader/scene/line.vert", "shader/scene/output.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    updateDeferredParam();
    
    vector<CyberCrater>::iterator it;
    for (it = ccs.begin(); it < ccs.end(); it++) {
        it->update();
        if (it->isDead()) ccs.erase(it);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    shadowLightPass->beginShadowMap(true);
    ofCamera sc = shadowLightPass->getCam();
    for (auto cc : ccs) {
        cc.draw(sc, true);
    }
    lightingPass->drawLights(sc, true);
    shadowLightPass->endShadowMap();
    
    deferred.begin(cam, true);
    for (auto cc : ccs) {
        cc.draw(cam, false);
    }
    lightingPass->drawLights(cam, false);
    deferred.end();
    
    if (isShow) panel.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'h') isShow = !isShow;
    if (key == ' ') ccs.push_back(CyberCrater(lineShader, arcShader));
}

void ofApp::setupDeferred(){
    deferred.init(ofGetWidth(), ofGetHeight());
    ssaoPass = deferred.createPass<SsaoPass>().get();
    
    shadowLightPass = deferred.createPass<ShadowLightPass>().get();
    shadowLightPass->lookAt(ofVec3f(0.0));
    shadowLightPass->setCam(75, 0, 4500);
    
    lightingPass = deferred.createPass<PointLightPass>().get();
    ofxDeferredShading::PointLight dlight;
    dlight.ambientColor = ofFloatColor(0.005);
    lightingPass->addLight(dlight);
    
    dlight.ambientColor = ofFloatColor(0.0);
    lightingPass->addLight(dlight);
    
    deferred.createPass<HdrBloomPass>();
    dofPass = deferred.createPass<DofPass>().get();
    
    // gui
    panel.setup();
    pl1.setName("Point light 1");
    pl1.add(pl1_pos.set("Position", ofVec3f(500,500,500), ofVec3f(-1000), ofVec3f(1000)));
    pl1.add(pl1_diff.set("Diffuse Color", ofFloatColor(0.4)));
    pl1.add(pl1_spe.set("Specular Color", ofFloatColor(1.0)));
    pl1.add(pl1_rad.set("Radius", 500, 100, 2000));
    pl1.add(pl1_int.set("Intensity", 1.2, 0.1, 3.0));
    panel.add(pl1);
    
    pl2.setName("Point light 2");
    pl2.add(pl2_pos.set("Position", ofVec3f(-600,700,200), ofVec3f(-1000), ofVec3f(1000)));
    pl2.add(pl2_diff.set("Diffuse Color", ofFloatColor(0.4)));
    pl2.add(pl2_spe.set("Specular Color", ofFloatColor(1.0)));
    pl2.add(pl2_rad.set("Radius", 500, 100, 2000));
    pl2.add(pl2_int.set("Intensity", 1.2, 0.1, 3.0));
    panel.add(pl2);
    
    ao.setName("Ambient Occlusion");
    ao.add(ao_rad.set("Occlusion Radius", 5.0, 0.1, 100.0));
    ao.add(ao_dark.set("Darkness", 0.8, 0.1, 5.0));
    panel.add(ao);
    
    shadow.setName("Shadow Light");
    shadow.add(sha_amb.set("Ambient", 0.0, 0.0, 1.0));
    shadow.add(sha_dif.set("Diffuse", 0.0, 0.0, 1.0));
    shadow.add(sha_dark.set("Shadow Darkness", 0.4, 0.0, 1.0));
    shadow.add(sha_blend.set("Lighting Blend", 0.4, 0.0, 1.0));
    panel.add(shadow);
    
    dof.setName("Defocus Blur");
    dof.add(dof_blur.set("Max Blur", 0.5, 0.0, 1.0));
    dof.add(dof_ape.set("Aperture", 0.1, 0.0, 1.0));
    dof.add(dof_focal.set("Focus Distance", 0.2, 0.0, 1.0));
    panel.add(dof);
}

void ofApp::updateDeferredParam(){
    
    lightingPass->getLightRef(0).position = pl1_pos.get();
    lightingPass->getLightRef(0).diffuseColor = pl1_diff.get();
    lightingPass->getLightRef(0).specularColor = pl1_spe.get();
    lightingPass->getLightRef(0).radius = pl1_rad.get();
    lightingPass->getLightRef(0).intensity = pl1_int.get();
    
    lightingPass->getLightRef(1).position = pl2_pos.get();
    lightingPass->getLightRef(1).diffuseColor = pl2_diff.get();
    lightingPass->getLightRef(1).specularColor = pl2_spe.get();
    lightingPass->getLightRef(1).intensity = pl2_int.get();
    lightingPass->getLightRef(1).radius = pl2_rad.get();
    
    ssaoPass->setOcculusionRadius(ao_rad.get());
    ssaoPass->setDarkness(ao_dark.get());
    
    shadowLightPass->setAmbientColor(ofFloatColor(sha_amb.get()));
    shadowLightPass->setDiffuseColor(ofFloatColor(sha_dif.get()));
    shadowLightPass->setDarkness(sha_dark.get());
    shadowLightPass->setBlend(sha_blend.get());
    
    shadowLightPass->setPosition(cos(ofGetElapsedTimef())*500, 2000.0, sin(ofGetElapsedTimef())*500);
    shadowLightPass->lookAt(ofVec3f(0.0));
    
    dofPass->setFocus(dof_focal.get());
    dofPass->setMaxBlur(dof_blur.get());
    dofPass->setAperture(dof_ape.get());
    
}
