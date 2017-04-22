#version 410 core

in vec2 UV;

uniform sampler2D cube_texture;

out vec3 color;

void main() {
    color = texture(cube_texture, UV).rgb;
}