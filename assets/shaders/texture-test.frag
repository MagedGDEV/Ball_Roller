#version 330 core

in Varyings {
    vec3 position;
    vec4 color;
    vec2 tex_coord;
    vec3 normal;
} fs_in;

out vec4 frag_color;

uniform sampler2D tex;

void main(){
    //TODO: (Req 5) Change the following line to read the fragment color
    //from the texture at the received texture coordinates
    //Using the texture function, you can read the color of the texture using the sampler and the given texture coordinates
    //The sampler is binded to a texture unit which is binded to a texture
    //So using the sampler, we will fetch the color of the pixel in the texture which has the passed tex_coord
    frag_color = texture(tex, fs_in.tex_coord);






}