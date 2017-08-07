#include "ofMain.h"
#include "PartObj.hpp"

class GenTunnel {
public:
    void setup();
    void update();
    void draw();

private:
    vector<PartObj> parts;
    int time = 0;
};
