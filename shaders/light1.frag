#version 330 core

struct Material{
  sampler2D diffuse_color;
  vec3 specular_color;
  float specular_shine;
};

struct Light {
    vec3 position;
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
};



uniform vec3 lightColor;
uniform vec3 view_position;
uniform Material material;
uniform Light light;


in vec3 Normal;
in vec3 FragPosition;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{

    vec3 surface_normal = normalize(Normal);

    vec3 ambient_color =
        light.ambient_color * vec3(texture(material.diffuse_color, TexCoord));

    vec3 light_direction = normalize(light.position - FragPosition);
    float normal_similarity = max(dot(surface_normal, light_direction), 0.0);

    vec3 diffuse_color =
        light.diffuse_color * normal_similarity
        * vec3(texture(material.diffuse_color, TexCoord));

    vec3 view_direction = normalize(view_position - FragPosition);
    vec3 reflect_direction = reflect(-light_direction, surface_normal);
    float specular_value = pow(max(dot(view_direction, reflect_direction), 0.0), material.specular_shine);

    vec3 specular_color = light.specular_color * (material.specular_color * specular_value);

    vec3 color = ambient_color + diffuse_color + specular_color;
    FragColor = vec4(color, 1.0);
}