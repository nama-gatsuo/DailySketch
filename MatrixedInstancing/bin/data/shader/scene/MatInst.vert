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

uniform vec2 size;
uniform vec3 rot1;
uniform vec3 scale1;
uniform vec3 trans1;
uniform vec3 rot2;
uniform vec3 scale2;
uniform vec3 trans2;

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

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

    float instanceX = mod(gl_InstanceID, size.x);
    float instanceY = floor(gl_InstanceID / size.x);

    float t1 = instanceX / size.x;
    float t2 = instanceY / size.y;

    trans(p, trans1 * t1);
    rotate(p, vec3(1,0,0), rot1.x * t1);
    rotate(p, vec3(0,1,0), rot1.y * t1);
    rotate(p, vec3(0,0,1), rot1.z * t1);
    scale(p, scale1.xxx * (0.5 + t1));

    trans(p, trans2 * t2);
    rotate(p, vec3(1,0,0), rot2.x * t2);
    rotate(p, vec3(0,1,0), rot2.y * t2);
    rotate(p, vec3(0,0,1), rot2.z * t2);
    scale(p, scale2.xxx * (0.5 + t2));

    float r = 1.4;

    vec4 pos = modelViewProjectionMatrix * vec4(p, 1.0);
    // if (pos.z > 0.0) {
    //     float d = length(pos.xyz);
    //     if (d < 0.001) d = 0.001;
    //     pos /= d;
    //     pos.z += 1.;
    //     pos.x *= r / pos.z;
    //     pos.y *= r / pos.z;
    //     pos.z = (d - nearClip) / (farClip - nearClip);
    //     pos.w = 1.0;
    // }

    gl_Position = pos;

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = color;
    vPosition = viewPos;
}
