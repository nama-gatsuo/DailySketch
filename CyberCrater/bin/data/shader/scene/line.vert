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

uniform float angle;
uniform float r1;
uniform float r2;

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

    // float angle = acos(dot(vec2(1,0), normalize(endPos.xz)) / length(endPos.xz));
    float dist = r2 - r1;

    p *= vec3(5., 5., dist);
    p += vec3(0, 0, r1 + dist * 0.5);
    p = rotateY(p, angle);

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vPosition = viewPos;
}
