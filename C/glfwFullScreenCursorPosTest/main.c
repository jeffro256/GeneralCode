#include <myglutils.h>
#include <stdio.h>

void printCallback(GLFWwindow* window, double xpos, double ypos) {
    printf("(%lf, %lf)\n", xpos, ypos);
}

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    GLFWwindow* window = glfwCreateWindow(960, 720, "Mouse Test", glfwGetPrimaryMonitor(), NULL);
    if (!window) {
        fprintf(stderr, "Cannot open window!\n");
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, printCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!setupGLEW()) return 1;
    glClearColor(0.5, 0.5, 0.8, 1.0);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
