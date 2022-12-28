#version 330 core

in Varyings{
    vec4 color;
    vec2 tex_coord;
    vec3 world;
    vec3 view;
    vec3 normal;
}fs_in;

#define TYPE_DIRECTIONAL 0
#define TYPE_POINT 1
#define TYPE_SPOT 2

#define MAX_LIGHTS 16

// create a struct to hold the light properties
struct Light{
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;

    float attenuation_constant, attenuation_linear, attenuation_quadratic;
    float inner_angle, outer_angle;
};

// create a struct to hold the material properties
struct Material{
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float shininess;
};

struct TexturedMaterial{
    sampler2D albedo;
    sampler2D specular;
    sampler2D ambient_occlusion;
    sampler2D roughness;
    sampler2D emissive;
};

uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform TexturedMaterial textured_material;
uniform int light_count;

out vec4 frag_color;

void main(){
    vec3 normal = normalize(fs_in.normal);
    vec3 view = normalize(fs_in.view);

    int count = min(light_count, MAX_LIGHTS);
    vec3 accum_light = vec3(0.0f);
    vec3 diffuse = texture(textured_material.albedo, fs_in.tex_coord).rgb;
    vec3 specular = texture(textured_material.specular, fs_in.tex_coord).rgb;
    vec3 ambient = material.diffuse * texture(textured_material.ambient_occlusion, fs_in.tex_coord).rgb;
    vec3 emissive = texture(textured_material.emissive, fs_in.tex_coord).rgb;
    float roughness = mix(0.05f, 1.0f, texture(textured_material.roughness, fs_in.tex_coord).r);
    float shininess = 2.0f / pow(clamp(roughness, 0.001f, 0.999f), 4.0f) - 2.0f;

    for(int i = 0; i<count; i++){
        Light light = lights[i];

        vec3 light_dir = vec3(0.0f);
        float attenuation = 1.0f;

        if(light.type == TYPE_DIRECTIONAL){
            light_dir = light.direction;
        }
        else{
            light_dir  = fs_in.world - light.position;
            float distance = length(light_dir);
            light_dir = light_dir / distance;
            attenuation =   1.0f / (light.attenuation_constant + 
                            light.attenuation_linear * distance + 
                            light.attenuation_quadratic * distance * distance);
            if (light.type == TYPE_SPOT){
                float angle = acos(dot(light_dir, light.direction));
                attenuation *= smoothstep(light.outer_angle, light.inner_angle, angle);
            }
        }

        vec3 reflected = reflect(light_dir, normal);
        float lambert = max(dot(normal, -light_dir), 0.0f);
        float phong = pow(max(dot(reflected, view), 0.0f), material.shininess);
        diffuse *= lambert;
        specular *= phong;
        accum_light += (diffuse + specular) * attenuation + ambient;
    }

    frag_color = vec4(accum_light + emissive, 1.0f);
}

