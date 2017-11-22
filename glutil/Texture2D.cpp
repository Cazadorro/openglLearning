//
// Created by shae on 11/21/17.
//

#include "Texture2D.h"

Texture2D::Texture2D() {
    GLuint texture_enum_name;
    glGenTextures(1, &texture_enum_name);
    m_texture_enum_name = texture_enum_name;

}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_texture_enum_name);

}

void Texture2D::setParameter(const GLenum &param_name, const GLfloat &value) {
    bind();
    glTexParameterf(GL_TEXTURE_2D, param_name, value);
    Texture2D::unbindAll();
}

void Texture2D::setParameter(const GLenum &param_name, const GLint &value) {
    bind();
    glTexParameteri(GL_TEXTURE_2D, param_name, value);
    Texture2D::unbindAll();
}

void Texture2D::setImage(const RawImage &raw_image, GLenum internal_format,
                         GLint lod_to_generate) {
    bind();
    glTexImage2D(GL_TEXTURE_2D, lod_to_generate, internal_format,
                 raw_image.getWidth(), raw_image.getHeight(), 0,
                 raw_image.getChannelEnum(), GL_UNSIGNED_BYTE,
                 raw_image.getData());
    Texture2D::unbindAll();
}

void Texture2D::generateMipmap() {
    bind();
    glGenerateMipmap(GL_TEXTURE_2D);
    Texture2D::unbindAll();
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture_enum_name);
}

void Texture2D::unbindAll() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::use(const GLenum &active_texture) {
    glActiveTexture(active_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture_enum_name);
}


