#include "logger.h"
#include "myglutils.h"
#include "physics_body.hpp"

#include <assert.h>
#include <cmath>
#include <glm/vec2.hpp>
#include <glm/gtx/string_cast.hpp> // @temp
#include <type_traits> // @temp

static const float square_points[] = {
    -0.10,  0.10,
     0.10,  0.10,
    -0.10, -0.10,
     0.10,  0.10,
     0.10, -0.10,
    -0.10, -0.10
};

int main() {
    if (!setupGLFW()) return 1;
    setupApple();

    set_log_file(fopen("pb.log", "a"));
    setDebug(true);
    setBind(true);

    GLFWwindow* window = glfwCreateWindow(640, 640, "Physics Body Test", NULL, NULL);
    if (!window) {
        log_msg(LOG_ERROR, "Failed to create window!\n");

        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!setupGLEW()) return 1;

    glClearColor(0.5, 0.5, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    log_msg(LOG_INFO, "###########################\n");
    log_msg(LOG_INFO, "Starting Physics Body Test!\n");
    log_msg(LOG_INFO, "###########################\n");
    log_msg(LOG_DEBUG, "PB is POD: %d\n", std::is_pod<PBody>::value);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    const char* vPath = "square_shader.vs.glsl";
    const char* fPath = "square_shader.fs.glsl";
    GLuint program = getProgramFromFiles(vPath, fPath);

    assert(vao && program);

    PBody body = { 80.0 };
    //body.mass = 80.0;

    int jumpLeft = 0;

    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        // DO PHYSICS
        body.applyForceY(-9.8);

        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            jumpLeft = 5;
        }

        if (jumpLeft) {
            body.applyForceY(30.0);
            jumpLeft--;
        }

        body.update(0.033);

        //log_msg(LOG_INFO, "Square Position 1: %s\n", glm::to_string(body.pos).c_str());

        if (body.y > 0.9) {
            body.y = 0.9;
            body.Vy = -std::abs(body.Vy * 0.75);
            jumpLeft = 0;
        }

        if (body.y < -0.9) {
            body.y = -0.9;
            body.Vy = std::abs(body.Vy * 0.75);
            jumpLeft = 0;
        }

        //log_msg(LOG_INFO, "Square Position 2: %s\n", glm::to_string(body.pos).c_str());

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(program);

        GLuint posID = glGetUniformLocation(program, "center");
        assert(posID != -1);
        glUniform2f(posID, body.x, body.y);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    log_msg(LOG_INFO, "###########################\n");
    log_msg(LOG_INFO, "Stopping...\n");
    log_msg(LOG_INFO, "###########################\n");

    glfwTerminate();
    return 0;
}
