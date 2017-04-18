#version 330 core

#define MAX_LIGHTS 100
uniform vec3 light_positions[MAX_LIGHTS];
uniform vec3 light_colors[MAX_LIGHTS];
uniform int num_lights;
uniform vec3 eye_pos;

in vec3 surface_pos;
in vec3 surface_normal;
in vec3 surface_color;

out vec3 frag_color;

vec3 phong_light(
    vec3 s_pos, vec3 s_normal, vec3 s_color, vec3 l_pos,
    vec3 l_color, vec3 e_pos, float amb_str, float diff_str,
    float spec_str, float shine) {

    vec3 light_dir = normalize(s_pos - l_pos);
    float diff_amount = max(dot(-light_dir, s_normal). 0.0) * diff_str;

    vec3 eye_dir = normalize(s_pos - e_pos);
    vec3 reflected = reflect(light_dir, s_normal);
    float spec_amount = pow(max(dot(-eye_dir, reflected), 0.0), shine) * spec_str;

    vec3 total_light_color = (amb_str + diff_amount + spec_amount) * l_color;
    vec3 result = total_light_color * s_color;

    return result;
}

void main() {
    vec3 light_sum = vec3(0, 0, 0);
    for (int i = 0; i < numLights; i++) {
        vec3 l_pos = light_positions[i];
        vec3 l_color = light_colors[i] / numLights; // I divide here to keep values less than 1

        light_sum += phong_light(surface_pos, surface_normal, surface_color,
                                 l_pos, l_color, eye_pos, 0.4, 1.0, 0.1, 32);
    }

    frag_color = light_sum;
}