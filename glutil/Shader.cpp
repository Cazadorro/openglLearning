//
// Created by shae on 11/20/17.
//

#include "Shader.h"
#include <iostream>

Shader::Shader(const std::string &shader_code, const GLenum shader_type) {
    const char *raw_shader_code = shader_code.c_str();
    m_shader = glCreateShader(shader_type);
    glShaderSource(m_shader, 1, &raw_shader_code, nullptr);
    glCompileShader(m_shader);
    checkLinkError();
}

Shader::operator GLuint() const {
    return m_shader;
}

Shader::~Shader() {
    glDeleteShader(m_shader);
}

void Shader::checkLinkError() {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR\n" << infoLog
                  << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}
