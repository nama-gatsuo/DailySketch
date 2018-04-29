#version 410

in float vDepth;
in vec4 vColor;
in vec4 vPos;

layout (location = 0) out vec4 outputColor0;
layout (location = 1) out vec4 outputColor1;
layout (location = 2) out vec4 outputColor2;
layout (location = 3) out vec4 outputColor3;

void main() {
    vec3 n;
    n.xy = gl_PointCoord.xy * 2.0 - 1.0;
    float d = length(n.xy);

    n.z = 1.0 - d;
    float alpha = smoothstep(0.0, 1.0, n.z);
    if (n.z < 0.001) discard;
    vec4 c = vec4(vColor.rgb * 1. / d, alpha) * vColor.a;

    outputColor0 = vec4(0.);
    outputColor1 = vPos;
    outputColor2 = vec4(vec3(0.), vDepth);

    if (dot(vColor, vColor) < dot(vec4(1.0), vec4(1.0))) c = vec4(0.);
    outputColor3 = c;

}
