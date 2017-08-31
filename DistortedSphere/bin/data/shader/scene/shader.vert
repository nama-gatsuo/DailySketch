#version 400
#pragma include "./noise3D.frag"
#pragma include "./random.frag"

uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
// uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
// in vec4 color; // oF Default
// in vec2 texcoord; // oF Default

uniform float farClip;
uniform float nearClip;

uniform float time;

out vec4 vPosition;
out float vDepth;
out float vNoise;

void main(){

    vec4 p = position;
    float noise = pow(cnoise(p.xyz * 0.02 + time), 2.);

    p.xyz += normal.xyz * noise * 100.;

    gl_Position = modelViewProjectionMatrix * p;

    vec4 viewPos = modelViewMatrix * p;
    vDepth = - viewPos.z / (farClip - nearClip);
    vPosition = viewPos;
    vNoise = noise;
}
