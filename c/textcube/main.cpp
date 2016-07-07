#include <logger.h>
#include <myglutils.h>

#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#define ROTATE 1

/*
    Clean Up:
    * Delete Buffers
	* Delete Vertex Arrays
	* Delete programs
	* Delete textures
	* Terminate GLFW
*/

GLuint program;
glm::mat4 rotation = glm::mat4(1.0);
glm::vec3 camPos = glm::vec3(0.0, 0.0, 5.0);
int buttonState = 0;
double mouseX = 0.0;
double mouseY = 0.0;

void updateMVP() {
    glm::mat4 projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 MVP = projection * view * rotation;
    
    GLuint MVPID = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
}

void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        buttonState = action;
    }
}

void _cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    xpos -= WIN_WIDTH / 2.0;
    ypos = WIN_HEIGHT - ypos - WIN_HEIGHT / 2.0;

    if (ROTATE) {
        if (buttonState == GLFW_PRESS) {
            glm::vec2 oldMouse = glm::vec2(mouseX, mouseY);
            glm::vec2 newMouse = glm::vec2(xpos, ypos);
            double dist = glm::distance(oldMouse, newMouse);

            if (dist > 0) {
                glm::vec3 mouseVec = glm::vec3(newMouse - oldMouse, camPos.z);
                glm::vec3 rotationAxis = glm::cross(mouseVec, camPos);
                float theta = M_PI * 2 - dist / 250.0;

                rotation = glm::rotate(glm::mat4(1.0), theta, rotationAxis) * rotation;
                updateMVP();
            }
        }
    }

    mouseX = xpos;
    mouseY = ypos;
}

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Textured Cube", NULL, NULL);
    if (!window) {
        log_msg(LOG_ERROR, "Could not open a GLFW3 window!\n");
        
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, _mouse_button_callback);
    glfwSetCursorPosCallback(window, _cursor_pos_callback);    

    if (!setupGLEW()) return 1;
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    static const int vertices = 12 * 3;
    static const GLfloat points[] = {
        -1, -1,  1,
         1, -1,  1,
        -1,  1,  1,
        -1,  1,  1,
         1, -1,  1,
         1,  1,  1,
         1, -1,  1,
         1, -1, -1,
         1,  1,  1,
         1,  1,  1,
         1, -1, -1, 
         1,  1, -1,
         1, -1, -1,
        -1, -1, -1,
         1,  1, -1,
         1,  1, -1,
        -1, -1, -1,
        -1,  1, -1,
        -1, -1, -1,
        -1, -1,  1,
        -1,  1, -1,
        -1,  1, -1,
        -1, -1,  1,
        -1,  1,  1,
        -1,  1,  1,
         1,  1,  1,
        -1,  1, -1,
        -1,  1, -1,
         1,  1,  1,
         1,  1, -1,
        -1, -1, -1,
         1, -1, -1,
        -1, -1,  1,
        -1, -1,  1,
         1, -1, -1,
         1, -1,  1,
    };
    
    static const GLfloat textureCoords[] = {
        0.00, 0.00,
        0.25, 0.00,
        0.00, 0.50,
        0.00, 0.50,
        0.25, 0.00,
        0.25, 0.50,
        0.00, 0.50,
        0.25, 0.50,
        0.00, 1.00,
        0.00, 1.00,
        0.25, 0.50,
        0.25, 1.00,
        0.25, 0.00,
        0.50, 0.00,
        0.25, 0.50,
        0.25, 0.50,
        0.50, 0.00,
        0.50, 0.50,
        0.25, 0.50,
        0.50, 0.50,
        0.25, 1.00,
        0.25, 1.00,
        0.50, 0.50,
        0.50, 1.00,
        0.50, 0.00,
        0.75, 0.00,
        0.50, 0.50,
        0.50, 0.50,
        0.75, 0.00,
        0.75, 0.50,
        0.50, 0.50,
        0.75, 0.50,
        0.50, 1.00,
        0.50, 1.00,
        0.75, 0.50,
        0.75, 1.00
    };
    
    GLuint pointBuffer;
    glGenBuffers(1, &pointBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint textureBuffer;
    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pointBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    const char* vsPath = "/Users/jeffaryan/Code/c/textcube/text_cube.vs.glsl";
    const char* fsPath = "/Users/jeffaryan/Code/c/textcube/text_cube.fs.glsl";
    program = getProgramFromFiles(vsPath, fsPath);
    
    if (!program) {
        log_msg(LOG_ERROR, "There was a problem opening shader program.\n");
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDeleteBuffers(1, &pointBuffer);
        glDeleteBuffers(1, &textureBuffer);
        glDeleteVertexArrays(1, &vao);
        glfwTerminate();
        
        return 1;
    }

    glUseProgram(program);
    updateMVP();
    
    GLuint texture = loadBMP("/Users/jeffaryan/Code/c/textcube/cube_texture.bmp");

    if (!texture) {
        log_msg(LOG_ERROR, "There was a problem opening shader.\n");

        // clean up
        return 1;
    }

    GLuint textureID = glGetUniformLocation(program, "cube_texture");
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
    
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, vertices);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    // clean up
    return 0;
}

void cleanup(GLuint pb, GLuint tb, GLuint va, GLuint tex) {
    
}
