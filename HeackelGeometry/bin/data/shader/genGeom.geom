#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices=81) out;

in vec4 pSeed[];

uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform float farClip;
uniform float nearClip;

uniform float f1;
uniform float f2;
uniform float f3;

out vec4 vPos;
out float vDepth;
out vec3 vBC;

void create(in vec3 v1, in vec3 v2, in vec3 v3){

    gl_Position = modelViewProjectionMatrix * vec4(v1, 1.);
    vPos = modelViewMatrix * vec4(v1, 1.);
    vDepth = - vPos.z / (farClip - nearClip);
    vBC = vec3(1,0,0);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v2, 1.);
    vPos = modelViewMatrix * vec4(v2, 1.);
    vDepth = - vPos.z / (farClip - nearClip);
    vBC = vec3(0,1,0);
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v3, 1.);
    vPos = modelViewMatrix * vec4(v3, 1.);
    vDepth = - vPos.z / (farClip - nearClip);
    vBC = vec3(0,0,1);
    EmitVertex();
    EndPrimitive();
}

void sub3(in vec3 v1, in vec3 v2, in vec3 v3){
    vec3 center = (v1 + v2 + v3) / 3.;
    vec3 n = normalize(cross(v2-v1, v3-v1)) * f3;

    create(v1, n + center, v2);
    create(v2, n + center, v3);
    create(v3, n + center, v1);
}

void sub2(in vec3 v1, in vec3 v2, in vec3 v3){
    vec3 center = (v1 + v2 + v3) / 3.;
    vec3 n = normalize(cross(v2-v1, v3-v1)) * f2;

    sub3(v1, n + center, v2);
    sub3(v2, n + center, v3);
    sub3(v3, n + center, v1);
}

void sub1(in vec3 v1, in vec3 v2, in vec3 v3){
    vec3 center = (v1 + v2 + v3) / 3.;
    vec3 n = normalize(cross(v2-v1, v3-v1)) * f1;

    sub2(v1, n + center, v2);
    sub2(v2, n + center, v3);
    sub2(v3, n + center, v1);
}


void main(void){

    sub1(pSeed[0].xyz,pSeed[1].xyz,pSeed[2].xyz);

}
