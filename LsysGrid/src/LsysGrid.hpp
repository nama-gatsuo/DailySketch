#pragma once
#include "ofMain.h"

struct Rule {
    Rule(char _a, string _b) : a(_a), b(_b) {};
    const char a;
    const string b;
};

class LsysGrid {
public:
    LsysGrid(){};
    void setup(){
        rules.push_back(Rule('F', "FF+[+F-F-F]-[-F+F+F]"));
    };
    void draw(){
        mesh.draw(OF_MESH_FILL);
    }
    void generate(){
        string nextSentence;
        
        for (int i = 0; i < sentence.length(); i++) {
            
            char current = sentence.at(i);
            bool found = false;
            
            for (int j = 0; j < rules.size(); j++) {
                
                if (current == 'F') {
                    nextSentence += rules[j].b;
                    found = true;
                    break;
                }
                
            }
            
            if (!found) {
                nextSentence += current;
            }
        }
        
        sentence = nextSentence;
        cout << sentence << endl;
    };
    void turtle(){
        vector<ofMatrix4x4> matStack;
        ofMatrix4x4 mat;
        mat.glTranslate(0, -1000, 0);
        mesh.clear();
        length *= 0.5;
        
        for (int i = 0; i < sentence.length(); i++) {
            
            char current = sentence.at(i);
            
            for (int j = 0; j < rules.size(); j++) {
                
                if (current == 'F') {
                    addBox(mat);
                    mat.glTranslate(0, length, 0);
                } else if (current == '+') {
                    mat.glRotate(90, 0, 0, 1);
                } else if (current == '-') {
                    mat.glRotate(90, 0, 1, 0);
                } else if (current == '[') {
                    matStack.push_back(mat);
                } else if (current == ']') {
                    mat = matStack.at(matStack.size() - 1);
                    
                    vector<ofMatrix4x4> newStack;
                    for (int i = 0; i < matStack.size() - 1; i++) {
                        newStack.push_back(matStack[i]);
                    }
                    matStack = newStack;
                }
                
            }
        }

    };    
private:
    void addBox(ofMatrix4x4 mat){
        ofFloatColor c;
        c.setHsb(0.5, 0.3, 0.8);
        
        mat.glTranslate(0, length*0.5, 0);
        
        ofMesh box = ofMesh::box(length*0.1, length*1.1, length*0.1, 1,1,1);
        for (int i = 0; i < box.getNumVertices(); i++) {
            ofVec3f v = box.getVertex(i) * mat;
            ofVec3f n = ((box.getNormal(i) + v) * mat - (v * mat)).normalize();
            
            box.setVertex(i, v);
            box.setNormal(i, n);
            
            box.addColor(c);
        }
        mesh.append(box);
    };
    
    string axiom = "F";
    string sentence = axiom;
    
    vector<Rule> rules;
    
    float length = 1000.0;
    ofVboMesh mesh;
};
