#version 450 core

in vec2 UV_vert_out_frag_in;

out vec4 out_Color;

uniform sampler2D TEXTURE_DIFFUSE_0;

void main() {
    out_Color = texture(TEXTURE_DIFFUSE_0, UV_vert_out_frag_in);
//    out_Color = vec4(1.0f);
    //        out_Color = vec4(POS_VERT_OUT_FRAG_IN, 1.0);
}
