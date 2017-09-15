#version 400

uniform float wireWidth;
uniform int isDrawFace;
uniform int isShadow;

in vec4 gPos;
in float gDepth;
in vec3 gNormal;
in vec3 gBC;

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

void main(void){

    if (isShadow == 1) {

        if(any(lessThan(gBC, vec3(wireWidth))) || isDrawFace == 1){
            outputColor0.r = gDepth;
            outputColor0.a = 1.0;
        } else {
            discard;
        }

    } else {

        if(any(lessThan(gBC, vec3(wireWidth)))){
            outputColor0 = vec4(1.);
        } else {
            if (isDrawFace == 1) outputColor0 = vec4(0., 0.02, 0.1, 1.0);
            else discard;
        }

        outputColor1 = gPos;
        outputColor2 = vec4(calcFlatNormal(gPos.xyz), gDepth);

        vec4 c = vec4(vec3(0.0), 1.0);
        if (dot(outputColor0, outputColor0) > dot(vec4(1.0), vec4(1.0))) c = outputColor0;
        outputColor3 = c;

    }
}
