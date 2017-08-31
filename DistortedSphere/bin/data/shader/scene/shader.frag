#version 400

in vec4 vPosition;
in float vDepth;
in float vNoise;

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
        vec3 n = calcFlatNormal(vPosition.xyz);
        vec3 col = vec3(0.3, 0.5, 1.3) * abs(vNoise) * 3.0;

        outputColor0 = vec4(col, 1.);
        outputColor1 = vPosition;
        outputColor2 = vec4(n, vDepth);

        if (dot(col, col) > dot(vec4(1.0), vec4(1.0))) {
            outputColor0 = vec4(vec3(0.0), 1.0);
            outputColor3 = vec4(col, 1.0);
        } else {
            outputColor3 = vec4(0.);
        }
    }

}
