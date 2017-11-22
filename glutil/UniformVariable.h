//
// Created by shae on 11/20/17.
//

#ifndef GRIDMAPDISPLAY_UNIFORMVARIABLE_H
#define GRIDMAPDISPLAY_UNIFORMVARIABLE_H

#include <glad/glad.h>
#include <string>


class ShaderProgram;

class UniformVariable {
    GLint m_uniform_location;
    GLuint m_parent_shader_program;
public:
    UniformVariable(const ShaderProgram &shader_program,
                    const std::string &variable_name);

    explicit operator GLint() const;

    bool isUniformParent(const ShaderProgram &shader_program) const;

private:


};


#endif //GRIDMAPDISPLAY_UNIFORMVARIABLE_H
