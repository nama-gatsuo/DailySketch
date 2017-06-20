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

uniform int num;
uniform float time;
uniform float radius;
uniform vec3 boxScale;
// uniform vec3 boxRot;
uniform vec3 rot;

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

    float inst = gl_InstanceID / float(num);

    scale(p, boxScale * vec3(1.,1.,sin(time+inst*PI*2.0)));
    rotate(p, vec3(1,0,0), inst * PI + time);

    p.y += radius;
    rotate(p, vec3(0,0,1), 2. * PI * inst + time);

    rotate(p, vec3(1,0,0), rot.x + time);
    rotate(p, vec3(0,1,0), rot.y - time);
    rotate(p, vec3(0,0,1), rot.z + time);

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = color;
    vPosition = viewPos;
}
