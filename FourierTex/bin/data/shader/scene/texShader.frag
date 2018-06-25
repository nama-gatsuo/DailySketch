#version 400

uniform float time;
uniform int ns[2];   // num
uniform float rs[2]; // radius
uniform int fs[2];   // freq
uniform float ps[2]; // power

in vec2 vTexCoord;
out vec4 outputColor;

const float PI = 3.14159265359;

float waveSum(int index, in vec2 uv) {
    float sum = 0.;
    float limit = ns[index];

    for (float i = 0.; i < 17.; i += 1.) {

        if (i >= limit) return sum;

        float divisor = 0.5 * ns[index];
        vec2 p = rs[index] * vec2(cos(PI / divisor * i), sin(PI / divisor * i));
        float dist = distance(p, uv);
        sum += ps[index] * cos(dist * PI * fs[index] - time);

    }
    return sum;
}

void main(){

    vec2 uv = vTexCoord / 512.;
    uv -= vec2(0.5);
    uv *= 2.;

    float sum = 0.;
    sum += waveSum(0, uv);
    sum += waveSum(1, uv);

    sum *= 0.5;
    sum += 0.5;

    outputColor = vec4(vec3(sum), 1.);

}
