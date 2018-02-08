#version 410
const float PI = 3.14159265358979323;
#pragma include "./random.frag"

in vec2 vTexCoord;

uniform vec2 texRes;
uniform float radius;
uniform float maxLife;

layout (location = 0) out vec4 outputColor1;
layout (location = 1) out vec4 outputColor2;

void main(){

    vec2 st = vTexCoord / texRes;
    float theta = 2. * PI * st.x;
    float rho = PI * st.y;

    vec3 pos = vec3(
            radius * sin(theta) * sin(rho),
            radius * cos(theta) * sin(rho),
            radius * cos(rho)
        );

    float life = maxLife * srand(vTexCoord);

    vec3 vel = normalize(vec3(srand(vTexCoord.xy)-0.5, srand(vTexCoord.x)-0.5, srand(vTexCoord.y)-0.5));

    outputColor1 = vec4(pos, life);
    outputColor2 = vec4(vel, 1.);
}
