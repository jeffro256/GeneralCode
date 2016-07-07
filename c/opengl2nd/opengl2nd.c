#include <stdio.h>
#include <time.h>
#include <myglutils.h>

void render(GLFWwindow* window, GLuint vao, GLuint shader);

float points[] = {
     0.0,  0.5,
     0.5, -0.5,
    -0.5, -0.5 
};

float colors[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
};

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Jeffrey", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Window creation failed.\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!setupGLEW()) return 1;

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    printf("Renderer: %s\n", renderer);
    printf("OpenGL Version: %s\n", version);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint p_buffer;
    glGenBuffers(1, &p_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, p_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint c_buffer;
    glGenBuffers(1, &c_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, c_buffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_buffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, c_buffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    const char* vertex_shader =
    "#version 410\n"
    "layout(location = 0) in vec2 pos;"
    "layout(location = 1) in vec3 in_color;\n"
    "out vec3 color;\n"
    "void main() {"
    "    color = in_color;"
    "    gl_Position = vec4(pos, 0.0, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 410\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main() {"
    "    frag_color = vec4(color, 1.0);"
    "}";

    GLuint program = getProgram(vertex_shader, fragment_shader);

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        render(window, vao, program);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void render(GLFWwindow* window, GLuint vao, GLuint shader) {
    if (window != glfwGetCurrentContext()) {
        glfwMakeContextCurrent(window);
        printf("Changing context.\n");
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
