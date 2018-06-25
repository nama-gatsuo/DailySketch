#version 400
in vec4 vPosition;
in float vDepth;
in float vFactor;

layout (location = 0) out vec4 outputColor0;
layout (location = 1) out vec4 outputColor1;
layout (location = 2) out vec4 outputColor2;
layout (location = 3) out vec4 outputColor3;

vec3 calcFlatNormal(vec3 posInViewSpace){
    vec3 dx = dFdx(posInViewSpace);
    vec3 dy = dFdy(posInViewSpace);
    vec3 n = normalize(cross(normalize(dx), normalize(dy)));

    return - n;
}

void main(){
    float c = vFactor;
    int ci = int(floor(c / 0.02));
    if (mod(ci, 20) == 0) {
        c = 1.01;
    } else {
        if (ci < 10 || ci > 40) discard;
        else c = 0.1;
    }

    vec3 n = calcFlatNormal(vPosition.xyz);

    outputColor0 = vec4(vec3(c), 1.);
    outputColor1 = vPosition;
    outputColor2 = vec4(n, vDepth);
    outputColor3 = c > 1. ? vec4(vec3(c), 1.) : vec4(0.,0.,0.,1.);
}
