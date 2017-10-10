#version 410

#pragma include "./noise3d.frag"
#pragma include "./curl-noise.frag"

in vec2 vTexCoord;

// current value
uniform sampler2DRect currentPosAndAge;
uniform sampler2DRect currentVel;
// start value
uniform sampler2DRect startPosAndAge;
uniform sampler2DRect startVel;

uniform float turbulence;
uniform float noiseStrength;
uniform float noiseScale;

layout (location = 0) out vec4 outputColor1;
layout (location = 1) out vec4 outputColor2;

void main(){

    vec4 posAndAge = texture(currentPosAndAge, vTexCoord);
    vec3 pos = posAndAge.rgb;
    vec3 vel = texture(currentVel, vTexCoord).rgb;
    float age = posAndAge.a;

    age -= 1.0;

    if (age < 0.) {
        vec4 sPosAndAge = texture(startPosAndAge, vTexCoord);
        pos = sPosAndAge.rgb;
        vel = texture(startVel, vTexCoord).rgb;
        age = sPosAndAge.a;
    }
    vel *= (1.001 - turbulence);
    vel += curlNoise(pos * noiseScale * 0.001) * noiseStrength * 0.01;
    pos += vel;

    outputColor1 = vec4(pos, age);
    outputColor2 = vec4(vel, 1.);
}
