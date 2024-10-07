#include "../include/Scene.h"
#include "../include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Texture

Texture::Texture(std::string path)
{
    stbi_set_flip_vertically_on_load(true);
    int nrChannels;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    
    unsigned char *data = stbi_load("image.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture(){}