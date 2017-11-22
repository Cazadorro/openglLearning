//
// Created by shae on 11/22/17.
//

#ifndef GRIDMAPDISPLAY_VERTEXBUFFEROBJECT_H
#define GRIDMAPDISPLAY_VERTEXBUFFEROBJECT_H

#include <glad/glad.h>

class VertexBufferObject {
    GLuint m_buffer;
public:
    VertexBufferObject(const GLsizeiptr &size, const GLvoid *data,
                       GLenum usage);

    ~VertexBufferObject();

    void bind();

    void setData(const GLsizeiptr &size, const GLvoid *data, GLenum usage);

    void updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data);

    static void unbindAll();

    explicit operator GLuint() const;

private:
};


#endif //GRIDMAPDISPLAY_VERTEXBUFFEROBJECT_H


