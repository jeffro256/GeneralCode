#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 in_color;

uniform mat4 MVP;

out vec3 color;

void main() {
    gl_Position = MVP * vec4(pos, 1.0);
    color = in_color;
}
