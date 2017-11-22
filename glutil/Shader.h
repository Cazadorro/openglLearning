//
// Created by shae on 11/20/17.
//

#ifndef GRIDMAPDISPLAY_SHADERT_H
#define GRIDMAPDISPLAY_SHADERT_H

#include <glad/glad.h>
#include <string>

class Shader {
    GLuint m_shader;
public:
    Shader(const std::string &shader_code, GLenum shader_type);

    explicit operator GLuint() const;

    ~Shader();

private:
    void checkLinkError();
};


#endif //GRIDMAPDISPLAY_SHADERT_H
