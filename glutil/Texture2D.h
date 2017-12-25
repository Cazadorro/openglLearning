//
// Created by shae on 11/21/17.
//

#ifndef GRIDMAPDISPLAY_TEXTURE2D_H
#define GRIDMAPDISPLAY_TEXTURE2D_H

#include <glad/glad.h>
#include "Image.h"

class Texture2D {
    GLuint m_texture_enum_name;
public:
    Texture2D();

    ~Texture2D();

    template<class ValueT>
    void
    setParameter(const GLenum &param_name, const ValueT &value) = delete;


    void setParameter(const GLenum &param_name, const GLfloat &value);

    void setParameter(const GLenum &param_name, const GLint &value);

    void setImage(const Image &raw_image, GLenum internal_format,
                  GLint lod_to_generate = 0);

    void defaultInit(const Image &raw_image, GLenum internal_format);

    void generateMipmap();

    void bind();

    static void unbindAll();

    void use(const GLenum &active_texture);

private:
};


#endif //GRIDMAPDISPLAY_TEXTURE2D_H
