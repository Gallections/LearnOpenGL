#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main() {
    // ambient
    // light is going to encode the ambient strength, and the material is going to contain the object color, ambient is just he objectColor * strength
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * material.diffuse;

    // specular
    vec3 reflecDir = reflect(-lightDir, norm);
    vec3 viewDir = viewPos - FragPos;
    float spec = pow(max(dot(reflecDir, viewDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}