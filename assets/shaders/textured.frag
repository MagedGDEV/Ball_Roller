#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
} fs_in;

out vec4 frag_color;

uniform vec4 tint;
uniform sampler2D tex;

void main(){
    //TODO: (Req 7) Modify the following line to compute the fragment color
    // by multiplying the tint with the vertex color and with the texture color 

    // we use texture instead of textureFetch because screen picture:texture picture ratio is not 1:1

    // texture coordinate is a normalized version of the pixel coordinate
    // texture coordinates are in the range [0, 1] in s and t
    // we sample from the texture using the normalized texture coordinates

    frag_color = tint * fs_in.color * texture(tex, fs_in.tex_coord);
}