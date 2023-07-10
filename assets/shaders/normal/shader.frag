#version 450

in vec3 POSITION_vert_out_frag_in;
in vec3 NORMAL_vert_out_frag_in;
in vec2 UV_vert_out_frag_in;

out vec4 out_Color;

uniform sampler2D TEXTURE_DIFFUSE_0;

void main() {
//    out_Color = texture(TEXTURE_DIFFUSE_0, UV_VERT_OUT_FRAG_IN);

    vec3 normalized_normal_color = normalize(NORMAL_vert_out_frag_in) * 0.5 + 0.5;
    out_Color = vec4(normalized_normal_color, 1.0);

//        out_Color = vec4(POS_VERT_OUT_FRAG_IN, 1.0);
}
