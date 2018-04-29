#version 400
precision mediump float;
#pragma include "../util/noise3d.frag"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

uniform float time;
out vec2 vTexCoord;
out vec4 vPosition;

const float PI = 3.14159265;
const float gridNum = 200.;
const float speed = 160.;
const float totalDist = 4000.;

void main(){
    vec4 p = position;
    float w = sin(time*0.3) + 3.;

    p.z = mod(p.z + totalDist/2. + time * speed, totalDist) - totalDist/2.;

    float hightFactor = 20. * (sin(time * 0.5) + 1.2);
    float noiseFactor = snoise(vec3(texcoord.x * 0.06 * w, sin(PI * texcoord.y / gridNum) * 5. * w, 0.));

    p.y += hightFactor * noiseFactor;
    vTexCoord = texcoord;
    vPosition = p;
}
