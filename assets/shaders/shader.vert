#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 uv;

out vec3 Vert_Out_Frag_In;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Vert_Out_Frag_In = aCol;
    TexCoord = uv;
}