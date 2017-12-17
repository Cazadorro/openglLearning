//
// Created by shae on 11/22/17.
//

#include "VertexAttributeLocation.h"

VertexAttributeLocation::VertexAttributeLocation(
        const ShaderProgram &shader_program, const std::string &variable_name) {
    m_attribute_location = glGetAttribLocation(
            static_cast<GLuint>(shader_program),
            variable_name.c_str());
    assert(m_attribute_location != -1);
}

VertexAttributeLocation::operator GLint() const {
    return m_attribute_location;
}

VertexAttributeLocation::operator GLuint() const {
    return static_cast<GLuint>(m_attribute_location);
}
