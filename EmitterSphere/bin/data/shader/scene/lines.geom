#version 400

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 24) out;

uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++

uniform float farClip;
uniform float nearClip;

uniform vec3 to;

in vec4 vPosition[];

out vec4 vPos;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

void createFace(in vec3 v1, in vec3 v2, in vec3 v3){
    vec3 n = normalize(cross(v2 - v1, v3 - v1));
    n = (normalMatrix * vec4(n, 1.0)).xyz;
    vec4 col = vec4(0.1, 0.2, 0.4, 1.0);

    vec4 viewPos = modelViewMatrix * vec4(v1, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(v1, 1.0);
    vPos = viewPos;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = n;
    vColor = col;
    EmitVertex();

    viewPos = modelViewMatrix * vec4(v2, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(v2, 1.0);
    vPos = viewPos;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = n;
    vColor = col;
    EmitVertex();

    viewPos = modelViewMatrix * vec4(v3, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(v3, 1.0);
    vPos = viewPos;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = n;
    vColor = col;
    EmitVertex();

    EndPrimitive();
}

void main(){

    for (int i = 0; i < gl_in.length(); i++) {

        vec3 from = vPosition[i].xyz;
        vec3 center = (from + to) * 0.5;
        float dist = distance(from, to);


        if (length(to) < length(from)) {
            createFace(vec3(0),vec3(0),vec3(0));
        } else {
            vec3 axisY = normalize(to - from);
            vec3 axisX = normalize(cross(axisY, vec3(0,1.,0)));
            vec3 axisZ = normalize(cross(axisX, axisY));

            vec3 belt[4];
            float thickness = min(1000./dist, 50.);
            belt[0] = center + axisX * thickness;
            belt[1] = center + axisZ * thickness;
            belt[2] = center - axisX * thickness;
            belt[3] = center - axisZ * thickness;

            for (int i = 0; i < 4; i++) {
                int i1 = i;
                int i2 = i == 3 ? 0 : i+1;

                createFace(from, belt[i1], belt[i2]);
                createFace(to, belt[i2], belt[i1]);
            }
        }



    }

}
