#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 Vert_Out_Frag_In;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Vert_Out_Frag_In = aCol;
}