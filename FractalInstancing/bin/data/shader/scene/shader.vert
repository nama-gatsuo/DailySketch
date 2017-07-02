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

uniform float an;
uniform float ds;
uniform float dt;
uniform vec3 bs;
uniform float slp;

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

    scale(p, bs*2.);

    for (int i = 0; i < 6; i++) {
        float ind = floor(float(gl_InstanceID) / pow(an, float(i)));
        scale(p, vec3(ds));
        rotate(p, vec3(0., 1., 0.), PI/an*2. * ind);
        trans(p, vec3(0, 0., dt));
        rotate(p, vec3(0., 0., 1.), PI/slp);
    }
    scale(p, vec3(10.));

    gl_Position = modelViewProjectionMatrix * vec4(p, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(p, 1.0);
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = color;
    vPosition = viewPos;
}
