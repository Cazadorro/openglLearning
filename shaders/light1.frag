#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambient_strength;
uniform float specular_strength;
uniform vec3 view_position;
uniform int specular_shine;

in vec3 Normal;
in vec3 FragPosition;
in vec3 LightPosition;

void main()
{

    vec3 surface_normal = normalize(Normal);

    vec3 ambient_color = ambient_strength * lightColor;

    vec3 light_direction = normalize(LightPosition - FragPosition);
    float normal_similarity = max(dot(surface_normal, light_direction), 0.0);
    vec3 diffuse_color = normal_similarity * lightColor;

    vec3 view_direction = normalize(view_position - FragPosition);
    vec3 reflect_direction = reflect(-light_direction, surface_normal);
    float specular_value = pow(max(dot(view_direction, reflect_direction), 0.0), specular_shine);
    vec3 specular_color = specular_strength * specular_value * lightColor;


    vec3 color = (ambient_color + diffuse_color + specular_color) * objectColor;
    FragColor = vec4(color, 1.0);
}