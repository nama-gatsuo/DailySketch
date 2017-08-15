#version 400

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2DRect sea;

out vec4 outputColor;

void main(){

    vec2 res = textureSize(sea);
    vec2 uv = vTexCoord * res;
    vec4 col = texture(sea, uv);

    bool isSea = (col.r+col.g+col.b)/3. > 0.001;
    if (isSea) discard;

    outputColor = vec4(0.2) + vColor * 0.5;

}
