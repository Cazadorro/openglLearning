//
// Created by shae on 11/22/17.
//

#include "VertexBufferObject.h"

#include <string>

VertexBufferObject::VertexBufferObject(const GLsizeiptr &size,
                                       const GLvoid *data,
                                       GLenum usage) {
    GLuint index;
    glGenBuffers(1, &index);
    m_index = index;

    setData(size, data, usage);

}

void VertexBufferObject::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
}

void VertexBufferObject::setData(const GLsizeiptr &size, const GLvoid *data,
                                 GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    VertexBufferObject::unbindAll();
}

void VertexBufferObject::unbindAll() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &m_index);
}

void VertexBufferObject::updateData(GLintptr offset, GLsizeiptr size,
                                    const GLvoid *data) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    VertexBufferObject::unbindAll();
}

VertexBufferObject::operator GLuint() const {
    return m_index;
}
