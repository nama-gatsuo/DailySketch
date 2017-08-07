#include "GenTunnel.hpp"

void GenTunnel::setup(){}

void GenTunnel::update(){
    
    if (time % 10 == 0) {
        
        PartObj p;
        float coin = ofRandom(1.0);
        if (coin < 0.35) {
            p.setup(MULTI_WALL);
        } else if (coin < 0.7) {
            p.setup(LATTICE);
        } else if (coin < 0.85) {
            p.setup(SPHERES);
        } else {
            p.setup(BLOCKS);
        }
        
        parts.push_back(p);
        
    }
    time++;
    
    vector<PartObj>::iterator it;
    for (it = parts.begin(); it < parts.end(); it++) {
        
        if (it->check()) {
            parts.erase(it);
        } else {
            it->update();
        }
    
    }
}

void GenTunnel::draw() {
    vector<PartObj>::iterator it;
    for (it = parts.begin(); it < parts.end(); it++) {
        it->draw();
        
    }
}

