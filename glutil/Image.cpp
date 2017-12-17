//
// Created by shae on 11/21/17.
//

#include <glad/glad.h>
#include "Image.h"
//#include "stbi_image_imp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(unsigned char *data, int width, int height, GLenum channels){
    m_data = data;
    m_width = width;
    m_height = height;
    m_channels = channels;
}

Image::Image(const std::string &file_location, const int chosenChannels) {
    int width;
    int height;
    int trueChannels;
    m_data = stbi_load(file_location.c_str(), &width,
                       &height, &trueChannels, chosenChannels);
    m_width = width;
    m_height = height;
    int channels = (chosenChannels != 0) ? chosenChannels : trueChannels;
    switch (channels) {
        case 1:
            m_channels = GL_RED;
            break;
        case 2:
            m_channels = GL_RG;
            break;
        case 3:
            m_channels = GL_RGB;
            break;
        case 4:
            m_channels = GL_RGBA;
            break;
        default:
            assert(false);
    }
}

Image::~Image() {
    stbi_image_free(m_data);
}

int Image::getWidth() const {
    return m_width;
}

int Image::getHeight() const {
    return m_height;
}

GLenum Image::getChannelEnum() const {
    return m_channels;
}

const unsigned char *Image::getData() const {
    return m_data;
}
