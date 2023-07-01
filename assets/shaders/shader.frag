#version 450

out vec4 out_Color;

void main() {
    out_Color = vec4(from_vert_to_frag, 1.0);
}
