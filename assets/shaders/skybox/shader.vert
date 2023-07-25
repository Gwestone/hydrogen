#version 450 core
layout (location = 0) in vec3 POS_IN;
layout (location = 1) in vec3 NORMAL_IN;
layout (location = 2) in vec2 UV_IN;

out vec3 POSITION_vert_out_frag_in;
out vec3 NORMAL_vert_out_frag_in;
out vec2 UV_vert_out_frag_in;

uniform mat4 TRANSFORM_IN;
uniform mat4 MODEL_IN;

void main()
{
    POSITION_vert_out_frag_in = POS_IN;
    NORMAL_vert_out_frag_in = NORMAL_IN;
    UV_vert_out_frag_in = UV_IN;
    gl_Position = TRANSFORM_IN * MODEL_IN * vec4(POS_IN.x, POS_IN.y, POS_IN.z, 1.0);
}