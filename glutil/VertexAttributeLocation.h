//
// Created by shae on 11/22/17.
//

#ifndef GRIDMAPDISPLAY_VERTEXATTRIBUTELOCATION_H
#define GRIDMAPDISPLAY_VERTEXATTRIBUTELOCATION_H

#include <glad/glad.h>
#include <string>
#include "ShaderProgram.h"

class VertexAttributeLocation {
    GLint m_attribute_location;
public:
    VertexAttributeLocation(const ShaderProgram &shader_program,
                            const std::string &variable_name);
    VertexAttributeLocation(GLint layout_location);
    explicit operator GLint() const;
    explicit operator GLuint() const;
;private:

};


#endif //GRIDMAPDISPLAY_VERTEXATTRIBUTELOCATION_H
