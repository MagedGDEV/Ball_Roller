#version 330 core

out vec4 frag_color;

// In this shader, we want to draw a checkboard where the size of each tile is (size x size).
// The color of the top-left most tile should be "colors[0]" and the 2 tiles adjacent to it
// should have the color "colors[1]".

//TODO: (Req 1) Finish this shader.

uniform int size = 32;
uniform vec3 colors[2];

void main(){

    // TODO: (Req 1) Finish this shader.


    // gl_FragCoord.xy is the position of the current pixel in the screen.
    // The x coordinate is the horizontal position and the y coordinate is the vertical position.
    // The origin of the coordinate system is the top-left corner of the screen.
    // The x coordinate increases to the right and the y coordinate increases to the bottom.
    // xy is a vec2, which is a 2D vector. You can access the x and y components of the vector
    // using the .x and .y attributes.
    // floor(gl_FragCoord.xy / size) will give you the position of the current pixel in the checkboard.
    
    vec2 elements = floor(gl_FragCoord.xy / size);
    // Check if the x and y coordinates of the current pixel are even or odd.
    if (mod(elements.x, 2) == 0) {
        if (mod(elements.y, 2) == 0) {
            // If both x and y are even, then the current pixel is of color 0.
            frag_color = vec4(colors[0], 1.0);
        } else {
            // If x is even and y is odd, then the current pixel is of color 1.
            frag_color = vec4(colors[1], 1.0);
        }
    } else {
        if (mod(elements.y, 2) == 0) {
            // If x is odd and y is even, then the current pixel is of color 1.
            frag_color = vec4(colors[1], 1.0);
        } else {
            // If both x and y are odd, then the current pixel is of color 0.
            frag_color = vec4(colors[0], 1.0);
        }
    }


}