#version 330 core
out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoords;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, fTexCoords);
}
