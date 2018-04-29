#version 410

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
in vec2 texcoord;

uniform float linearDepthScalar;
uniform float time;
uniform sampler2DRect posAndLifeTex;

out float vDepth;
out vec4 vColor;
out vec4 vPos;

void main() {

    vec4 samp = texture(posAndLifeTex, texcoord);
    vec3 pos = samp.rgb;
    float life = samp.a;

    vColor = vec4(vec3(2.), 1. - life);
    vPos = modelViewMatrix * vec4(pos, 1.0);
    vDepth = - vPos.z * linearDepthScalar;

    gl_Position = modelViewProjectionMatrix * vec4(pos, 1.0);
    gl_PointSize = 800. / gl_Position.w;
}
