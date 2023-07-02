#version 450

in vec3 Vert_Out_Frag_In;
in vec2 TexCoord;

out vec4 out_Color;

uniform sampler2D ourTexture;
uniform sampler2D faceTexture;

void main() {
    out_Color = mix(texture(ourTexture, TexCoord), texture(faceTexture, TexCoord), 0.2);
//        out_Color = texture(faceTexture, TexCoord);
}
