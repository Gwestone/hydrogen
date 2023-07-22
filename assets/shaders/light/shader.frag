#version 450

in vec3 POSITION_vert_out_frag_in;
in vec3 NORMAL_vert_out_frag_in;
in vec2 UV_vert_out_frag_in;

in vec3 FRAG_COORD_vert_out_frag_in;

out vec4 out_Color;

//uniform sampler2D TEXTURE_DIFFUSE_0;
//uniform sampler2D TEXTURE_SPECULAR_0;

struct Material {
    sampler2D TEXTURE_DIFFUSE_0;
    sampler2D TEXTURE_SPECULAR_0;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//uniform vec3 LIGHT_COLOR_IN;
//uniform vec3 LIGHT_POS_IN;
uniform vec3 CAMERA_POS_IN;

uniform Material material;
uniform Light light;


void main() {

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    //calculate attenuation
    float distance    = length(light.position - FRAG_COORD_vert_out_frag_in);
    float attenuation = 1.0 / (constant + linear * distance +
    quadratic * (distance * distance));

    //calculate ambient
    vec3 ambient = attenuation * light.ambient * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));

    //calculate diffuse
    //normalized normal of surface
    vec3 normal = normalize(NORMAL_vert_out_frag_in);
    //normalized direction of light got from substraction of vectors
    vec3 lightDirection = normalize(FRAG_COORD_vert_out_frag_in - light.position);
    //calculate similarity of normal vector and light directon vector
    float diff = max(dot(lightDirection, normal), 0);
    vec3 diffuse = attenuation * diff * light.diffuse * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));

    //calculate specular
    //calculate camera view direction vector
    vec3 viewDir = normalize(CAMERA_POS_IN - FRAG_COORD_vert_out_frag_in);
    //calc light reflect vector
    vec3 reflectDir = reflect(-lightDirection, normal);
    //calc closeness of reflected and view vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = attenuation * spec * light.specular * vec3(texture(material.TEXTURE_SPECULAR_0, UV_vert_out_frag_in));


    out_Color = vec4(ambient + diffuse + specular, 1);


//    out_Color = vec4(color, 1) * texture(TEXTURE_DIFFUSE_0, UV_vert_out_frag_in);
//        out_Color = vec4(POS_VERT_OUT_FRAG_IN, 1.0);
}
