#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdio.h>

#include "myglutils.hpp"

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Perspective", 0, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create window.\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!setupGLEW()) return 1;

    glClearColor(0.2, 0.0, 0.8, 1.0);

    const GLfloat vertices[] = {
        -1.0, -1.0,
         1.0, -1.0,
         0.0,  1.0
    };

    const GLchar* vert_shader =
    "#version 410 core\n"
    "in vec2 pos;"
    "uniform mat4 MVP;"
    "void main() {"
    "    gl_Position = MVP * vec4(pos, 0.0, 1.0);"
    "}";

    const GLchar* frag_shader =
    "#version 410 core\n"
    "out vec4 color;"
    "void main() {"
    "    color = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";

    GLuint shader = getShader(vert_shader, frag_shader);

    if (!shader) {
        fprintf(stderr, "Shader compilation failed.\n");
        glfwTerminate();
        return 1;
    }

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint MVPID = glGetUniformLocation(shader, "MVP");

    glm::mat4 perspective = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 view = glm::lookAt(glm::vec3(4.0, 3.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 MVP = perspective * view;
    
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}
