//
// Created by shae on 11/22/17.
//

#ifndef GRIDMAPDISPLAY_VERTEXATTRIBUTE_H
#define GRIDMAPDISPLAY_VERTEXATTRIBUTE_H

#include "VertexAttributeLocation.h"
#include "VertexBufferObject.h"

class VertexAttributeObject {
private:
    GLuint m_index;
public:
    VertexAttributeObject();

    ~VertexAttributeObject();

    void bind();

    void setVertexBufferObject(VertexBufferObject &VBO);

    void setAttributeData(VertexAttributeLocation &attribute_location, GLint size, GLenum type, GLboolean normalized,
                          GLsizei stride, std::size_t offset = 0);

    void enableAttribute(VertexAttributeLocation &attribute_location);

    void disableAttribute(VertexAttributeLocation &attribute_location);

    static void unbindAll();

    explicit operator GLuint() const;

};


#endif //GRIDMAPDISPLAY_VERTEXATTRIBUTE_H
