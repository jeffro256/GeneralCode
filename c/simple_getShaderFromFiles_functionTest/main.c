#include <stdio.h>

#include <myglutils.h>

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple Test, You can ignore window!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!setupGLEW()) return 1;

    GLuint shader = getShaderFromFiles("my_shader.vs", "my_shader.fs");
    printf("Shader ID: %u\n", shader);

    if (!shader) {
        printf("Bad!\n");
        return 1;
    }

    printf("Good!\n");
    return 0;
}
