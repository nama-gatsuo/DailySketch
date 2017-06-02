#version 400

uniform sampler2DRect tex;
uniform float rawFft[256];
in vec2 vTexCoord;

out vec4 outputColor;

void main(){

    if (vTexCoord.y < 1.0) {
        int i = int(vTexCoord.x);
        outputColor.r = rawFft[i];
    } else {
        vec2 st = vTexCoord;
        st.y -= 1.0;
        outputColor.r = texture(tex, st).r;
    }
    outputColor.a = 1.0;
}
