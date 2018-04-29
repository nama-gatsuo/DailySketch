#version 400

uniform float time;
uniform int shadowFlag;

flat in float discardFlag;
in vec2 vUV;
in vec4 vPos;
in float vDepth;

const float PI = 3.14159265;
const float resY = 200.;

layout (location = 0) out vec4 outputColor0;
layout (location = 1) out vec4 outputColor1;
layout (location = 2) out vec4 outputColor2;
layout (location = 3) out vec4 outputColor3;

vec3 calcFlatNormal(vec3 pos){
    vec3 dx = dFdx(pos);
    vec3 dy = dFdy(pos);
    vec3 n = normalize(cross(normalize(dx), normalize(dy)));
    return n;
}

void main(){
    if (discardFlag > 0.9999) {
        discard;
    } else {
        if (shadowFlag == 1) {
            outputColor0.r = vDepth;
            outputColor0.a = 1.;
        } else {
            vec3 n = calcFlatNormal(vPos.xyz);

            float thres = 0.96;

            vec3 c;
            if (mod(vUV.y,1.) > thres || mod(vUV.x,1.) > thres) {
                c = mix(vec3(2.,1.0,1.5), vec3(1.0,1.2,2.0), sin(vUV.y / resY * PI * 2.) * 1.1 + 0.5);
            } else {
                c = vec3(0);
            }

            outputColor0 = vec4(c, 1.);
            outputColor1 = vPos;
            outputColor2 = vec4(-n, vDepth);

            if (dot(c, c) < dot(vec3(1.0), vec3(1.0))) c = vec3(0.);
            outputColor3 = vec4(c, 1.);
        }

    }

}
