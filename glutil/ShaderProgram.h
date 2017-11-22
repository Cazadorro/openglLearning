//
// Created by shae on 11/20/17.
//

#ifndef GRIDMAPDISPLAY_SHADERPROGRAM_H
#define GRIDMAPDISPLAY_SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>
#include "Shader.h"


class UniformVariable;

class ShaderProgram {
    GLuint m_program_id;
public:
    ShaderProgram();

    ~ShaderProgram();

    void attachShader(const Shader &shader);

    void link();

    void use();

    explicit operator GLuint() const;

    template<class ValueT>
    void
    setUniform(const UniformVariable &uniform, const ValueT &value) = delete;

    void setUniform(const UniformVariable &uniform, const GLfloat &value);

    void setUniform(const UniformVariable &uniform, const GLint &value);

    void setUniform(const UniformVariable &uniform, const GLuint &value);

    void setUniform(const UniformVariable &uniform, const glm::vec2 &value);

    void setUniform(const UniformVariable &uniform, const glm::ivec2 &value);

    void setUniform(const UniformVariable &uniform, const glm::uvec2 &value);

    void setUniform(const UniformVariable &uniform, const glm::vec3 &value);

    void setUniform(const UniformVariable &uniform, const glm::ivec3 &value);

    void setUniform(const UniformVariable &uniform, const glm::uvec3 &value);

    void setUniform(const UniformVariable &uniform, const glm::vec4 &value);

    void setUniform(const UniformVariable &uniform, const glm::ivec4 &value);

    void setUniform(const UniformVariable &uniform, const glm::uvec4 &value);

    void setUniform(const UniformVariable &uniform, const glm::mat2 &value);

    void setUniform(const UniformVariable &uniform, const glm::mat3 &value);

    void setUniform(const UniformVariable &uniform, const glm::mat4 &value);

private:
    void checkLinkError();
};


#endif //GRIDMAPDISPLAY_SHADERPROGRAM_H
