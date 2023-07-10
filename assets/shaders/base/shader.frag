#version 450

in vec2 UV_VERT_OUT_FRAG_IN;
in vec3 POS_VERT_OUT_FRAG_IN;

out vec4 out_Color;

uniform sampler2D TEXTURE_DIFFUSE_0;

void main() {
    out_Color = texture(TEXTURE_DIFFUSE_0, UV_VERT_OUT_FRAG_IN);
//        out_Color = vec4(POS_VERT_OUT_FRAG_IN, 1.0);
}
