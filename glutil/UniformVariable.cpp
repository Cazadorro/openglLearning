//
// Created by shae on 11/20/17.
//

#include "UniformVariable.h"
#include "ShaderProgram.h"

UniformVariable::UniformVariable(const ShaderProgram &shader_program,
                                 const std::string &variable_name) {
    m_uniform_location = glGetUniformLocation(
            static_cast<GLuint>(shader_program),
            variable_name.c_str());
    assert(m_uniform_location != -1);
    m_parent_shader_program = static_cast<GLuint>(shader_program);
}

UniformVariable::operator GLint() const {
    return m_uniform_location;
}

bool
UniformVariable::isUniformParent(const ShaderProgram &shader_program) const {
    return m_parent_shader_program == static_cast<GLuint>(shader_program);
}


