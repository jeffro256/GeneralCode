#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "myglutils.hpp"

static const int vertices = 12 * 3;
static const GLfloat points[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
};

static GLfloat colors[vertices * 3];

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Colored Cube", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Window creation failed.\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!setupGLEW()) return 1;

    srand(time(NULL));
    for (int i = 0; i < sizeof(colors); i++) {
        GLfloat color = (GLfloat) rand() / RAND_MAX;
        colors[i] = color;
    }

    glClearColor(0.2, 0.0, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint p_buffer;
    glGenBuffers(1, &p_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, p_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint c_buffer;
    glGenBuffers(1, &c_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, c_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, c_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    const char* vertex_shader =
    "#version 410\n"
    "layout(location = 0) in vec3 pos;"
    "layout(location = 1) in vec3 in_color;"
    "out vec3 color;"
    "uniform mat4 MVP;"
    "void main() {"
    "    gl_Position = MVP * vec4(pos, 1.0);"
    "    color = in_color;"
    "}";

    const char* fragment_shader =
    "#version 410\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main() {"
    "    frag_color = vec4(color, 1.0);"
    "}";

    GLuint shader = getShader(vertex_shader, fragment_shader);
    GLuint MVPID = glGetUniformLocation(shader, "MVP");
    
    //START MAKE MATRIX
    glm::mat4 projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 view = glm::lookAt(glm::vec3(4.0, 3.0, -3.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 MVP = projection * view;
    //END MAKE MATRIX

    glUseProgram(shader);    
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        //START DRAW
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertices);
        //END DRAW

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
