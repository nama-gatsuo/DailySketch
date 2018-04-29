#version 410
precision highp float;

#pragma include "../util/noise3d.frag"
#pragma include "../util/curlNoise.frag"
#pragma include "../util/random.frag"

in vec2 vTexCoord;

// current value
uniform sampler2DRect posAndLifeTex;
uniform sampler2DRect velTex;

// parameter
uniform float noiseStrength;
float noiseScale = 0.04;

uniform int createFlag;
uniform vec3 emitPos;
uniform vec3 prevPos;
uniform float dt;
uniform float speed;

layout (location = 0) out vec4 outputColor1;
layout (location = 1) out vec4 outputColor2;

void main(){

    vec4 samp = texture(posAndLifeTex, vTexCoord);
    vec3 pos = samp.rgb;
    float life = samp.a;
    vec3 vel = texture(velTex, vTexCoord).rgb;

    if (life < 1.) {
        vel *= 0.95; // turbulance
        vel += curlNoise(pos * noiseScale) * noiseStrength * dt;
        pos += vel;
        life += 0.003;
    } else {
        vec3 dir = normalize(emitPos - prevPos);
        pos = mix(emitPos, prevPos, rand(vTexCoord * 0.01) * 4.);
        vel = - (emitPos - prevPos) * 2. + normalize(vec3(srand(vTexCoord.x), srand(vTexCoord.y), srand(vTexCoord.x + vTexCoord.y))) * 0.08;
        // vel *= 2.;
        life = createFlag == 1 ? rand(vTexCoord * 1.11) : 0.;
    }

    pos.z += speed * dt;

    outputColor1 = vec4(pos, life);
    outputColor2 = vec4(vel, 1.);
}
