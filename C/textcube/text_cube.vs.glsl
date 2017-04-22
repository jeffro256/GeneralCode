#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 inUV;

uniform mat4 MVP;

out vec2 UV;

void main() {
    gl_Position = MVP * vec4(pos, 1.0);
    
    UV = inUV;
}