#version 410

uniform mat4 modelViewProjectionMatrix;
in vec2 texcoord;

uniform sampler2DRect currentDataTex;
uniform sampler2DRect startDataTex;
uniform vec4 fromColor;
uniform vec4 toColor;
uniform float pointSize;

out vec4 vColor;

void main() {

    vec4 posAndAge = texture(currentDataTex, texcoord);
    float maxage = texture(startDataTex, texcoord).a;
    vec3 pos = posAndAge.xyz;
    float age = posAndAge.a;

    float life = age / maxage;
    vColor = mix(toColor, fromColor, life);
    // vColor = vec4(1.);
    gl_Position = modelViewProjectionMatrix * vec4(pos, 1.0);
    gl_PointSize = 100. * pointSize * life / gl_Position.w;
}
