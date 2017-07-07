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

uniform int total;

uniform vec3 fromTrans;
uniform vec3 toTrans;
uniform vec3 fromRotate;
uniform vec3 toRotate;
uniform vec3 fromScale;
uniform vec3 toScale;

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

float linearInterp(float value, float from, float to){
    return (to - from) * value + from;
}

vec3 linearInterp(float value, in vec3 from, in vec3 to){
    return (to - from) * value + from;
}

float cosineInterp(float value, float from, float to){
    return (to - from) * cos(PI * value) + from;
}

vec3 cosineInterp(float value, in vec3 from, in vec3 to){
    return (to - from) * cos(PI * value) + from;
}

float waveInterp(float value, float from, float to, float freq){
    return (to - from) * cos(PI * 2. * value * freq) + from;
}

vec3 waveInterp(float value, in vec3 from, in vec3 to, float freq){
    return (to - from) * cos(PI * 2. * value * freq) + from;
}

void trans(inout vec3 v, in vec3 t){
    v += t;
}

void main(){
    vec3 p = position.xyz;

    float value = float(gl_InstanceID) / float(total);

    vec3 s = cosineInterp(value, fromScale, toScale);
    scale(p, s);

    vec3 r = linearInterp(value, fromRotate, toRotate);
    r.y = cosineInterp(value, fromRotate.y, toRotate.y);
    rotate(p, vec3(1.,0,0), r.x);
    rotate(p, vec3(0,1.,0), r.y);
    rotate(p, vec3(0,0,1.), r.z);

    vec3 t = linearInterp(value, fromTrans, toTrans);
    t.x = waveInterp(value, fromTrans.x, toTrans.x, 2.);
    t.x = waveInterp(value, fromTrans.z, toTrans.z, 2.);
    t -= toTrans * 0.5;
    trans(p, t);

    scale(p, vec3(100.));

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = color;
    vPosition = viewPos;
}
