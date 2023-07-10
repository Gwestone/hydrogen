#version 450

in vec3 POSITION_vert_out_frag_in;
in vec3 NORMAL_vert_out_frag_in;
in vec2 UV_vert_out_frag_in;

in vec3 FRAG_COORD_vert_out_frag_in;

out vec4 out_Color;

uniform sampler2D TEXTURE_DIFFUSE_0;

uniform vec3 LIGHT_COLOR_IN;
uniform vec3 LIGHT_POS_IN;
uniform vec3 CAMERA_POS_IN;

void main() {

    //calculate ambient
    vec3 ambient = 0.2 * LIGHT_COLOR_IN;

    //calculate diffuse
    //normalized normal of surface
    vec3 normal = normalize(NORMAL_vert_out_frag_in);
    //normalized direction of light got from substraction of vectors
    vec3 lightDirection = normalize(FRAG_COORD_vert_out_frag_in - LIGHT_POS_IN);
    //calculate similarity of normal vector and light directon vector
    float diff = max(dot(lightDirection, normal), 0);
    vec3 diffuse = 0.5 * diff * LIGHT_COLOR_IN;

    //calculate specular
    //calculate camera view direction vector
    vec3 viewDir = normalize(CAMERA_POS_IN - FRAG_COORD_vert_out_frag_in);
    //calc light reflect vector
    vec3 reflectDir = reflect(-lightDirection, normal);
    //calc closeness of reflected and view vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = 0.3 * spec * LIGHT_COLOR_IN;


    vec3 color = (ambient + diffuse + specular);


    out_Color = vec4(color, 1) * texture(TEXTURE_DIFFUSE_0, UV_vert_out_frag_in);
//        out_Color = vec4(POS_VERT_OUT_FRAG_IN, 1.0);
}
