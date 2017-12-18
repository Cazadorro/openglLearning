#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_matrix;
uniform vec3 light_position;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPosition;
out vec3 LightPosition;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0f);
    FragPosition = vec3(view * model * vec4(inPos, 1.0f));
    Normal = normal_matrix * inNormal;
    LightPosition = vec3(view * vec4(light_position, 1.0));
//	TexCoord = vec2(inTexCoord.x, inTexCoord.y);
}