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

uniform float dscale[6];
uniform int division;
uniform float translate[6];
uniform vec3 boxSize;
uniform int index;

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

const float PI = 3.14159265359;

void rotate(inout vec3 v, in vec3 axis, float angle){
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    mat3 m = mat3(
        oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
        oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c
    );
    v = m * v;
}

void scale(inout vec3 v, in vec3 s){
    mat3 m = mat3(
        s.x, 0.0, 0.0,
        0.0, s.y, 0.0,
        0.0, 0.0, s.z
    );
    v = m * v;
}

void trans(inout vec3 v, in vec3 t){
    v += t;
}

void main(){
    vec3 p = position.xyz;

    scale(p, boxSize);

    for (int i = 0; i < 7; i++) {
        float ind = floor(float(gl_InstanceID) / pow(division, float(i)));

        rotate(p, vec3(0., 1., 0.), PI/division * 2. * ind);
        scale(p, vec3(dscale[i]));
        trans(p, vec3(0,0, translate[i]));
        rotate(p, vec3(0., 0., 1.), PI / 2.);
    }
    scale(p, vec3(3.));

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = color * ( 0.1 + index * 0.19 );
    vPosition = viewPos;
}
