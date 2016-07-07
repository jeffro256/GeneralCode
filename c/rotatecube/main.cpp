#include <myglutils.h>
#include <logger.h>

// FOR RANDOM COLORS
#include <stdlib.h>
#include <time.h>

#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

// For ease's sake
using namespace glm;

const vec3 camPos = vec3(0.0, 0.0, 5.0);

int mouseState = 0;
float mouseX = 0;
float mouseY = 0;
mat4 rotation = rotate(mat4(1), 1.0f, vec3(1, 1, 1));
int rotationChanged = 0;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        mouseState = action;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    xpos -= WINDOW_WIDTH / 2.0;
    ypos = WINDOW_HEIGHT - ypos - WINDOW_HEIGHT / 2.0;
    
    if (mouseState == GLFW_PRESS) {
        // calculate rotation. I can cheat a little because my camera is at (0, 0, 5)
        vec2 oldMouse = vec2(mouseX, mouseY);
        vec2 newMouse = vec2((float) xpos, (float) ypos);
        float dist = distance(oldMouse, newMouse);
        
        if (dist != 0) {
            vec3 mouseVec = vec3(newMouse - oldMouse, camPos.z);
            vec3 rotationAxis = cross(mouseVec, camPos);
            rotation = rotate(mat4(1), (float) M_PI * 2.0f - dist / 150.0f, rotationAxis) * rotation;
            rotationChanged = true;
        }
    }
    
    mouseX = xpos;
    mouseY = ypos;
}

void updateMVP(GLuint program) {
    mat4 projection = perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    mat4 view = lookAt(camPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    mat4 MVP = projection * view * rotation;
    
    GLuint MVPID = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rotating Cube", NULL, NULL);
    if (!window) {
        log_msg(LOG_ERROR, "Failed to create GLFW3 window.");

        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    if (!setupGLEW()) return 1;

    const int vertices = 12 * 3;
    const GLfloat points[] = {
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,
        -1.0, -1.0, -1.0,
        -1.0,  1.0,  1.0,
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
         1.0, -1.0,  1.0
    };
    
    GLfloat colors[vertices * 3];
    
    srand(time(NULL));
    for (int i = 0; i < vertices * 3; i++) {
        colors[i] = (GLfloat) rand() / RAND_MAX;
    }
   
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    GLuint pointVBO;
    glGenBuffers(1, &pointVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint colorVBO;
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    GLuint program = getProgramFromFiles("cube_shader.vs.glsl", "cube_shader.fs.glsl", argv[0]);
    glUseProgram(program);
    updateMVP(program);
    
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, vertices);
        
        if (rotationChanged) {
            updateMVP(program);
        }
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    
    return 0;
}
