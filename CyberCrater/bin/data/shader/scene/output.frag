#version 400
in vec4 vPosition;
in float vDepth;
in vec3 vNormal;
in vec4 vColor;

uniform int isShadow;

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

    if (isShadow == 1) {
        outputColor0.r = vDepth;
        outputColor0.a = 1.0;
    } else {
        outputColor0 = vec4(1., 1., 1., 1.);
        outputColor1 = vPosition;
        outputColor2 = vec4(calcFlatNormal(vPosition.xyz), vDepth);

        vec4 c = vec4(vec3(0.0), 1.0);
        if (dot(outputColor0, outputColor0) > dot(vec4(1.0), vec4(1.0))) c = outputColor0;
        outputColor3 = c;
    }
}
