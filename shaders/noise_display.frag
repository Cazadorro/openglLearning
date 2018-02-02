#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D noise_texture;

void main()
{
	FragColor = texture(noise_texture, TexCoord);
}