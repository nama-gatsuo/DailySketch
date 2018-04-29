#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default

uniform float linearDepthScalar;

in vec4 vPosition[];
in vec2 vTexCoord[];
smooth out vec4 vPos;
smooth out vec2 vUV;
smooth out float vDepth;
flat out float discardFlag;

void main(void){
    float d = 0;
    if (distance(vPosition[0], vPosition[2]) > 200.f) {
        d = 1.;
    }

    for (int i = 0; i < 3; i++) {
        vPos = modelViewMatrix * vPosition[i];
        vUV = vTexCoord[i];
        vDepth = - vPos.z * linearDepthScalar;
        discardFlag = d;
        gl_Position = modelViewProjectionMatrix * vPosition[i];
        EmitVertex();
    }
    EndPrimitive();

}
