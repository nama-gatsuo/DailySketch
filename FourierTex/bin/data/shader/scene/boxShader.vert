#version 400
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

uniform float linearDepthScalar;
uniform sampler2DRect fourierTex;
uniform float hFactor;

out vec4 vPosition;
out float vDepth;
out float vFactor;

void main(){

    vec3 n = normalize(position.xyz);
    float h = texture(fourierTex, texcoord * 512).r;
    vec4 p = position + vec4(n, 0.) * h * hFactor;

    vec4 viewPos = modelViewMatrix * p;
    vPosition = viewPos;
    vDepth = - viewPos.z * linearDepthScalar;
    vFactor = h;

    gl_Position = modelViewProjectionMatrix * p;
}
