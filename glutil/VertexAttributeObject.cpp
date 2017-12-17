//
// Created by shae on 11/22/17.
//

#include "VertexAttributeObject.h"

VertexAttributeObject::VertexAttributeObject() {
    GLuint index;
    glGenVertexArrays(1, &index);
    m_index = index;

}

VertexAttributeObject::~VertexAttributeObject() {
    glDeleteVertexArrays(1, &m_index);
}

void VertexAttributeObject::bind() {
    glBindVertexArray(m_index);
}

void VertexAttributeObject::setVertexBufferObject(VertexBufferObject &VBO) {
    bind();
    VBO.bind();
    unbindAll();
}

void VertexAttributeObject::setAttributeData(VertexAttributeLocation &attribute_location, GLint size, GLenum type,
                                       GLboolean normalized, GLsizei stride, std::size_t offset) {
    bind();
    glVertexAttribPointer(static_cast<GLuint>(attribute_location), size, type, normalized, stride, (void*)offset);
    enableAttribute(attribute_location);
    unbindAll();
}

void VertexAttributeObject::enableAttribute(VertexAttributeLocation &attribute_location) {
    bind();
    glEnableVertexAttribArray(static_cast<GLuint>(attribute_location));
    unbindAll();
}

void VertexAttributeObject::disableAttribute(VertexAttributeLocation &attribute_location) {
    bind();
    glDisableVertexAttribArray(static_cast<GLuint>(attribute_location));
    unbindAll();
}

void VertexAttributeObject::unbindAll() {
    glBindVertexArray(0);
}

VertexAttributeObject::operator GLuint() const {
    return m_index;
}
