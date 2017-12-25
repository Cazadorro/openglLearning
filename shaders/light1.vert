#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;

out vec3 FragPosition;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0f);
    FragPosition = vec3(view * model * vec4(inPos, 1.0f));
    Normal = normal_matrix * inNormal;
    TexCoords = inTexCoords;
}