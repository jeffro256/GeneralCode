#version 410

in vec2 pos;
uniform vec2 center;

void main() {
    gl_Position = vec4(center.x + pos.x, center.y + pos.y, 0.0, 1.0);
}
