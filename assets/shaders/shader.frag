#version 450

in vec3 Vert_Out_Frag_In;

out vec4 out_Color;

void main() {
    out_Color = vec4(Vert_Out_Frag_In, 1.0);
}
