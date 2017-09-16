#version 400
#pragma include "./rand.frag"
uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

uniform float farClip;
uniform float nearClip;

uniform int total;
uniform float radius;
uniform float startAngle;
uniform float endAngle;

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

vec3 rotateY(in vec3 p, in float angle){
    mat3 m = mat3(
        cos(angle), 0, sin(angle),
        0., 1., 0.,
        -sin(angle), 0, cos(angle)
    );
    return m * p;
}

void main(){
    vec3 p = position.xyz;

    float theta = (endAngle - startAngle) / float(total);
    if (theta < 0.01) theta = 0.;
    float width = (radius + 5.) * sin(theta * 0.5) * 2.;

    p *= vec3(width, 5., 5.);
    p += vec3(0, 20 * rand(radius), radius);
    p = rotateY(p, startAngle + theta * float(gl_InstanceID));

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vPosition = viewPos;
}
