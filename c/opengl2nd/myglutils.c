#include <stdio.h>
#include "myglutils.h"

static void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "ERROR CODE %d:\n", error);
    fprintf(stderr, "%s\n", description);
}

int setupGLFW() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        fprintf(stderr, "GLFW3 initialization failed.\n");

        return 0;
    }

    return 1;
}

int setupGLEW() {
    glewExperimental = GL_TRUE;
    GLenum glewErr;
    
    if ((glewErr = glewInit()) != GLEW_OK) {
        fprintf(stderr, "%s\n", glewGetString(glewErr));
        fprintf(stderr, "GLEW initialization failed.\n");

        glfwTerminate();
        return 0;
    }

    return 1;
}

void setupApple() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLuint getShader(const char* vertexShader, const char* fragmentShader) {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vs);
    glAttachShader(shader, fs);
    glLinkProgram(shader);

    return shader;
}
