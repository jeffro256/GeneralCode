#version 330 core

uniform mat4 view_projection_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_transform_matrix;

in vec3 model_pos;
in vec3 model_color;
in vec3 model_normal;

out vec3 surface_pos;
out vec3 surface_color;
out vec3 surface_normal;

void main() {
    gl_Position = view_projection_matrix * model_matrix * vec4(model_pos, 1.0);

    surface_pos = vec3(model_matrix * vec4(model_pos, 1.0));
    surface_color = model_color;
    surface_normal = normalize(vec3(normal_transform_matrix * vec4(model_normal, 1.0)));
}