#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;


out Varyings {
    vec3 normal;
    vec3 view;
    vec3 world;
    vec2 tex_coord;
    vec4 color;
} vs_out;

uniform mat4 object_to_world;
uniform mat4 object_to_world_it;
uniform mat4 v_p;
uniform vec3 eye;

void main(){
    vec3 world = (object_to_world * vec4(position, 1.0)).xyz;
    gl_Position = v_p * vec4(world, 1.0);
    vs_out.normal = (object_to_world_it * vec4(normal, 0.0)).xyz;
    vs_out.view = eye - world;
    vs_out.world = world;
    vs_out.tex_coord = tex_coord;
    vs_out.color = color;
}