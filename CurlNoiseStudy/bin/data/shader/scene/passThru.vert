#version 410
precision mediump float;

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

smooth out vec2 vTexCoord;

void main() {
    vTexCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}
