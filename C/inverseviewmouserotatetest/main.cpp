#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdio.h>
using namespace glm;

int main() {
    vec2 mouseOld = vec2(1.0, 1.0);
    vec2 mouseNew = vec2(2.0, -1.0);
    vec2 mouseDiff = mouseNew - mouseOld;
    vec3 camPos = vec3(4.0, 3.0, -3.0);
    mat4 viewMatrix = lookAt(camPos, vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 projection = perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    mat4 MVP = projection * viewMatrix;
    mat4 IMVP = inverse(MVP);
    vec4 mouseDiffReal = IMVP * vec4(mouseDiff, 0.0, 0.0);
    printf("Cam Pos: %s\n", to_string(camPos).c_str());
    printf("Mouse Diff: %s\n", to_string(mouseDiff).c_str());
    printf("Mouse Diff Real: %s\n", to_string(mouseDiffReal).c_str());    

    return 0;
}
