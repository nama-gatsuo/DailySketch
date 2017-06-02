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

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec2 vTexCoord;
out vec4 vColor;

void main(){
    float r = 1.4;
    
    vec4 pos = modelViewProjectionMatrix * position;
     if (pos.z > 0.0) {
         float d = length(pos.xyz);
         if (d < 0.001) d = 0.001;
         pos /= d;
         pos.z += 1.;
         pos.x *= r / pos.z;
         pos.y *= r / pos.z;
         pos.z = (d - nearClip) / (farClip - nearClip);
         pos.w = 1.0;
     }
    
    gl_Position = pos;

    
//    gl_Position = modelViewProjectionMatrix * position;

    vec4 viewPos = modelViewMatrix * position;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vTexCoord = texcoord;
    vColor = color;
    vPosition = viewPos;
}
