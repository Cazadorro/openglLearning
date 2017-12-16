//
// Created by shae on 11/20/17.
//

#include "ShaderProgram.h"
#include "UniformVariable.h"

ShaderProgram::ShaderProgram() {
    m_program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_program_id);
}

void ShaderProgram::attachShader(const Shader &shader) {
    glAttachShader(m_program_id, static_cast<GLuint>(shader));
}

void ShaderProgram::link() {
    glLinkProgram(m_program_id);
    checkLinkError();
}

void ShaderProgram::use() {
    glUseProgram(m_program_id);
}

ShaderProgram::operator GLuint() const{
    return m_program_id;
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const GLfloat &value) {
    assert(uniform.isParentProgram(*this));
    glUniform1f(static_cast<GLint>(uniform), value);
}

void
ShaderProgram::setUniform(const UniformVariable &uniform, const GLint &value) {
    assert(uniform.isParentProgram(*this));
    glUniform1i(static_cast<GLint>(uniform), value);
}

void
ShaderProgram::setUniform(const UniformVariable &uniform, const GLuint &value) {
    assert(uniform.isParentProgram(*this));
    glUniform1ui(static_cast<GLint>(uniform), value);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::vec2 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform2fv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::ivec2 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform2iv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::uvec2 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform2uiv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::vec3 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform3fv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::ivec3 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform3iv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::uvec3 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform3uiv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::vec4 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform4fv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::ivec4 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform4iv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::uvec4 &value) {
    assert(uniform.isParentProgram(*this));
    glUniform4uiv(static_cast<GLint>(uniform), 1, &value[0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::mat2 &value) {
    assert(uniform.isParentProgram(*this));
    glUniformMatrix2fv(static_cast<GLint>(uniform), 1, GL_FALSE,
                       &value[0][0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::mat3 &value) {
    assert(uniform.isParentProgram(*this));
    glUniformMatrix3fv(static_cast<GLint>(uniform), 1, GL_FALSE,
                       &value[0][0]);
}

void ShaderProgram::setUniform(const UniformVariable &uniform,
                               const glm::mat4 &value) {
    assert(uniform.isParentProgram(*this));
    glUniformMatrix4fv(static_cast<GLint>(uniform), 1, GL_FALSE,
                       &value[0][0]);
}

void ShaderProgram::checkLinkError() {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program_id, 1024, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR \n" << infoLog
                  << "\n -- --------------------------------------------------- -- "
                  << std::endl;
    }
}


