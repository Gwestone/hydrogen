#version 450 core
layout (location = 0) in vec3 POS_IN;
layout (location = 1) in vec3 NORMAL_IN;
layout (location = 2) in vec2 UV_IN;

out vec3 POS_VERT_OUT_FRAG_IN;
out vec2 UV_VERT_OUT_FRAG_IN;

uniform mat4 TRANSFORM_IN;

void main()
{
    UV_VERT_OUT_FRAG_IN = UV_IN;
    POS_VERT_OUT_FRAG_IN = POS_IN;
    gl_Position = TRANSFORM_IN * vec4(POS_IN.x, POS_IN.y, POS_IN.z, 1.0);
}