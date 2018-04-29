#version 400
in vec4 vPos;
in float vDepth;
in vec3 vBC;

uniform float wireWidth;

layout (location = 0) out vec4 outputColor0;
layout (location = 1) out vec4 outputColor1;
layout (location = 2) out vec4 outputColor2;

vec3 calcFlatNormal(vec3 posInViewSpace){
    vec3 dx = dFdx(posInViewSpace);
    vec3 dy = dFdy(posInViewSpace);
    vec3 n = normalize(cross(normalize(dx), normalize(dy)));

    return - n;
}

void main(){

    vec3 n = calcFlatNormal(vPos.xyz);
    if(any(lessThan(vBC, vec3(wireWidth)))){
        outputColor0 = vec4(vec3(1.) * max(dot(n, vec3(1.)), 0.4), 1.);
        outputColor1 = vPos;
        outputColor2 = vec4(n, vDepth);
    } else {
        discard;
    }


}
