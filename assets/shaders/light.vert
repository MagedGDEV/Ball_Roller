#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 normal;

// perform object to world transformation
uniform mat4 object_to_world;
// inverse transpose will be used to transform the surface normal
uniform mat4 object_to_world_inv_transpose; 

// perform world to clip transformation
uniform mat4 view_projection;
// camera position in the world space
uniform vec3 eye;

out Varyings {
    vec4 color;
    vec2 tex_coord;
    vec3 world;
    vec3 view;
    vec3 normal;
} vsout;

void main() {
    // get the position of the vertex in the world space
    vsout.world = (object_to_world * vec4(position, 1.0f)).xyz;
    // get view vector
    vsout.view = eye - vsout.world;
    // get the surface normal in the world space
    // w component of the normal is 0 since it's a vector
    vsout.normal = normalize((object_to_world_inv_transpose * vec4(normal, 0.0f)).xyz);
    // transform the vertex to clip space using view_projection matrix
    gl_Position = view_projection * vec4(vsout.world, 1.0);
    // pass the color and texture coordinates to the fragment shader
    vsout.color = color;
    vsout.tex_coord = tex_coord;
}