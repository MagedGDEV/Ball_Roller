

#include "texture-utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

our::Texture2D* our::texture_utils::empty(GLenum format, glm::ivec2 size){
    our::Texture2D* texture = new our::Texture2D();
    //TODO: (Req 11) Finish this function to create an empty texture with the given size and format
    //Then, we need to tell Opengl how our pixels will be aligned to be transfered from RAM to VRAM
    ///The default value is 4 which means that each row of pixels will be aligned to 4 bytes
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    //Now we can upload the image data to the texture
    //The first argument is the target texture which is GL_TEXTURE_2D
    //The second argument is the mipmap level which is 0 for the base level
    //The third argument is the internal format of the texture which is GL_RGBA8
    //The fourth and fifth arguments are the width and height of the texture
    //The sixth argument is the border which is 0
    //The seventh and eighth arguments are the format and type of the pixel data which is GL_RGBA and GL_UNSIGNED_BYTE
    //The last argument is the actual pixel data
    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    return texture;
}

our::Texture2D* our::texture_utils::loadImage(const std::string& filename, bool generate_mipmap) {
    glm::ivec2 size;
    int channels;
    //Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    //We need to till stb to flip images vertically after loading them
    stbi_set_flip_vertically_on_load(true);
    //Load image data and retrieve width, height and number of channels in the image
    //The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha (RGBA)
    //Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char* pixels = stbi_load(filename.c_str(), &size.x, &size.y, &channels, 4);
    if(pixels == nullptr){
        std::cerr << "Failed to load image: " << filename << std::endl;
        return nullptr;
    }

    // Create a texture
    our::Texture2D* texture = new our::Texture2D();
    //Bind the texture such that we upload the image data to its storage
    //TODO: (Req 5) Finish this function to fill the texture with the data found in "pixels"
    //First, we need to bind the texture to GL_TEXTURE_2D
    texture->bind();
    
    //Then, we need to tell Opengl how our pixels will be aligned to be transfered from RAM to VRAM
    ///The default value is 4 which means that each row of pixels will be aligned to 4 bytes
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    //Now we can upload the image data to the texture
    //The first argument is the target texture which is GL_TEXTURE_2D
    //The second argument is the mipmap level which is 0 for the base level
    //The third argument is the internal format of the texture which is GL_RGBA8
    //internalformat (GLint): The format in which the texture data will be stored in the VRAM. Since we have 4 channels (8 bits each) , we will store it as GL_RGBA8.
    //The fourth and fifth arguments are the width and height of the texture
    //The sixth argument is the border which is 0
    //The seventh and eighth arguments are the format and type of the pixel data which is GL_RGBA and GL_UNSIGNED_BYTE
    //format (GLenum): this is the format of the data as it is stored in the array "data" on the RAM. Since we have 4 components, we use GL_RGBA.
    //type (GLenum): this is the data type of each component in the array "data" on the RAM. We stored it as uint8 so we pick GL_UNSIGNED_BYTE.
    //The last argument is the actual pixel data. The function will read the data and send it to the GPU.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    //Afterwards, we will check if it is needed to generate mipmaps for this texture
    //If the boolean is true, we will generate mipmaps for this texture
    //This function will generate the mip map for the texture. It will automatically generate all the mip level till we reach a mip level whose size is 1x1 pixel.
    if(generate_mipmap)
        glGenerateMipmap(GL_TEXTURE_2D);

    //Finally, we need to unbind the texture
    texture->unbind();

    stbi_image_free(pixels); //Free image data after uploading to GPU
    return texture;
}
