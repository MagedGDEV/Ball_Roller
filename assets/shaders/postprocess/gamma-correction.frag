#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;
out vec4 frag_color;


void main(){
    //TODO: Modify this shader to apply color correction to the scene
    frag_color = texture(tex, tex_coord);

    // TODO: Apply gamma correction to the scene
    float gamma = 1.2;
    frag_color = vec4(pow(frag_color.r, 1.0/gamma), pow(frag_color.g, 1.0/gamma), pow(frag_color.b, 1.0/gamma), 1.0);
}