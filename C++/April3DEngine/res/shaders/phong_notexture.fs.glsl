#version 330 core

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 camera_pos;

in vec3 surface_pos;
in vec3 surface_color;
in vec3 surface_normal;

out vec3 frag_color;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light_color;

    float light_dir = normalize(surface_pos - light_pos);
    float diff_strength = max(dot(surface_normal, light_dir), 0.0);
    vec3 diffuse = diff_strength * light_color;

    frag_color = (ambient + diffuse) * surface_color;
}