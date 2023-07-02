#version 450

in vec3 Vert_Out_Frag_In;
in vec2 TexCoord;

out vec4 out_Color;

uniform sampler2D ourTexture;

void main() {
    out_Color = texture(ourTexture, TexCoord) * vec4(Vert_Out_Frag_In, 1.0);
}
