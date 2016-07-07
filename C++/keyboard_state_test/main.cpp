#include <logger.h>
#include <myglutils.h>
#include "keyboard_state.hpp"

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Keyboard State Test", NULL, NULL);
    if (!window) {
        log_msg(LOG_ERROR, "Window creation failed.\n");

        return 1;
    }

    //KeyboardState keyboard;

    glfwMakeContextCurrent(window);
    //addKeyListener(keyboard);
    glfwSetKeyCallback(window, listenerKeyCallback);

    if (!setupGLEW()) {
        log_msg(LOG_ERROR, "GLEW setup failed.\n");

        return 1;
    }

    glClearColor(0.5, 0.5, 0.8, 1.0);

    log_msg(LOG_INFO, "This was a fail, it never worked.\n");

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        /*if (keyboard.getKeyState(GLFW_KEY_UP)) {
            printf("What's up? The sky's up.\n");
        }*/

        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
