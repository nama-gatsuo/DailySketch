#version 400
// uniform mat4 modelViewMatrix; // oF Default
// uniform mat4 modelViewProjectionMatrix; // oF Default
// uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
// in vec4 normal; // oF Default
// in vec4 color; // oF Default
// in vec2 texcoord; // oF Default

out vec4 pSeed;

void main(){
    pSeed = position;
}
