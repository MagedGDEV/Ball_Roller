#version 330 core

in Varyings {
    vec3 normal;
    vec3 view;
    vec3 world;
    vec2 tex_coord;
} fs_in;

out vec4 frag_color;

struct Material {
    sampler2D albedo;
    sampler2D specular;
    sampler2D roughness;
    sampler2D ambient_occlusion;
    sampler2D emission;
};

#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    vec3 attenuation;
    vec2 cone_angles;
};

#define MAX_LIGHTS 8

uniform Material material;
uniform int light_count;
uniform Light lights[MAX_LIGHTS];

void main(){
    vec3 normal = normalize(fs_in.normal);
    vec3 view = normalize(fs_in.view);

    vec3 material_albedo = texture(material.albedo, fs_in.tex_coord).rgb;
    vec3 material_specular = texture(material.specular, fs_in.tex_coord).rgb;
    float roughness = texture(material.roughness, fs_in.tex_coord).r;
    float shininess = 2.0f/pow(clamp(roughness, 0.001f, 0.999f), 4.0f) - 2.0f;
    vec3 material_emission = texture(material.emission, fs_in.tex_coord).rgb;
    float material_ao = texture(material.ambient_occlusion, fs_in.tex_coord).r;

    frag_color = vec4(material_emission, 1);

    for(int i = 0; i < min(MAX_LIGHTS, light_count); i++){
        Light light = lights[i];

        vec3 light_dir = light.direction;
        if(light.type != DIRECTIONAL){
            light_dir = normalize(fs_in.world - light.position);
        }

        vec3 diffuse = material_albedo * light.color * max(0, dot(normal, -light_dir));
        vec3 reflected = reflect(light_dir, normal);
        vec3 specular = material_specular * light.color * pow(max(0, dot(view, reflected)), shininess);
        vec3 ambient = material_ao * material_albedo * 0.1;

        float attenuation = 1;
        if(light.type != DIRECTIONAL){
            float d = distance(light.position, fs_in.world);
            attenuation *= 1.0/dot(light.attenuation, vec3(1, d, d*d));
            if(light.type == SPOT){
                float angle = acos(dot(light.direction, light_dir));
                attenuation *= smoothstep(light.cone_angles.y, light.cone_angles.x, angle);
            }
        }
        frag_color.rgb += (diffuse + specular) * attenuation + ambient;
    }
}