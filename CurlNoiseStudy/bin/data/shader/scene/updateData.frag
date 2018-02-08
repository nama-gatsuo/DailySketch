#version 410

#pragma include "./noise3d.frag"
#pragma include "./curl-noise.frag"
#pragma include "./random.frag"

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
uniform vec3 pos;
uniform vec3 prevPos;

layout (location = 0) out vec4 outputColor1;
layout (location = 1) out vec4 outputColor2;

void main(){

    vec4 posAndAge = texture(currentPosAndAge, vTexCoord);
    vec3 p = posAndAge.rgb;
    vec3 vel = texture(currentVel, vTexCoord).rgb;
    float age = posAndAge.a;

    age -= 1.0;

    if (age < 0.) {
        vec4 sPosAndAge = texture(startPosAndAge, vTexCoord);
        p = sPosAndAge.rgb + mix(prevPos, pos, srand(vTexCoord));
        vel = texture(startVel, vTexCoord).rgb + normalize(pos - prevPos) * srand(0.1 * vTexCoord) * 0.3;
        age = sPosAndAge.a;
    }
    vel *= (1.001 - turbulence);
    vel += curlNoise(p * noiseScale * 0.001) * noiseStrength * 0.01;
    p += vel;

    outputColor1 = vec4(p, age);
    outputColor2 = vec4(vel, 1.);
}
