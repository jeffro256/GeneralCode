#version 330 core

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 eye_pos;

in vec3 surface_pos;
in vec3 surface_normal;
in vec3 surface_color;

out vec3 frag_color;

void main() {
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * light_color;

    vec3 light_dir = normalize(surface_pos - light_pos);
    float diff_strength = max(dot(surface_normal, -light_dir), 0.0);
    vec3 diffuse = diff_strength * light_color;

    float spec_strength = 0.5;
    float spec_focus = 128;
    vec3 eye_dir = normalize(surface_pos - eye_pos);
    vec3 reflected = reflect(light_dir, surface_normal);
    float spec_amount = pow(max(dot(-eye_dir, reflected), 0.0), spec_focus);
    vec3 specular = spec_strength * spec_amount * light_color;

    frag_color = (ambient + diffuse + specular) * surface_color;
}