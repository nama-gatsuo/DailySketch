#include "ofMain.h"
#include "CommonUtil.hpp"

namespace FractInst {
    class Tree {
    public:
        void setup();
        void update();
        void draw(ofCamera cam, bool isShadow);
        void randomize();
    private:
        const int depth = 7;
        ofShader shader;
        ofVboMesh mesh;
        
        int division;
        vector<SmoothValue> scale;
        vector<SmoothValue> translate;
        
        SmoothPoint boxSize;
        
        vector<int> num;
    };
}




