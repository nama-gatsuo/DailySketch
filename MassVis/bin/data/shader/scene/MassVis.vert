#version 400
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

uniform float farClip;
uniform float nearClip;

uniform sampler2DRect soundTex;
uniform int historySize;
uniform int fftSize;

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

void main(){
    vec4 p = position;

    vec2 size = textureSize(soundTex);

    float instanceX = mod(gl_InstanceID, size.x);
    float instanceY = floor(gl_InstanceID / size.x);

    float val = texture(soundTex, vec2(instanceX, instanceY)).r;

    vec2 offset = vec2(1.0);
    float height = val * 40.0;
    p.y *= height;
    p.y += height * 2.0;

    p.x += (5.0 + offset.x) * instanceX;
    p.z += (5.0 + offset.y) * (instanceY - size.y * 0.5);

    gl_Position = modelViewProjectionMatrix * p;

    vec4 viewPos = modelViewMatrix * p;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = vec4(vec3(0.1,0.2,0.3) * (1.0 + val * 4.0), 1.0);
    vPosition = viewPos;
}
