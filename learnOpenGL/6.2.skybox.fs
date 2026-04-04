#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoords);
    // we are not setting the fourthe channel to be fully opaque because we 
    // are drawing the background directly and alpha wouldn't matter so much.
}