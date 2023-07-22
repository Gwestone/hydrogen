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
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//uniform vec3 LIGHT_COLOR_IN;
//uniform vec3 LIGHT_POS_IN;
uniform vec3 CAMERA_POS_IN;

uniform Material material;
//uniform Light light;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(NORMAL_vert_out_frag_in);
    vec3 viewDir = normalize(CAMERA_POS_IN - FRAG_COORD_vert_out_frag_in);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FRAG_COORD_vert_out_frag_in, viewDir);
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    out_Color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));
    vec3 specular = light.specular * spec * vec3(texture(material.TEXTURE_SPECULAR_0, UV_vert_out_frag_in));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.TEXTURE_DIFFUSE_0, UV_vert_out_frag_in));
    vec3 specular = light.specular * spec * vec3(texture(material.TEXTURE_SPECULAR_0, UV_vert_out_frag_in));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}