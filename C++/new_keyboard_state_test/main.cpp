#include <logger.h>
#include <myglutils.h>

#include "key_input_store.hpp"

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();

    setDebug(1);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Key Input Store", NULL, NULL);
    if (!window) {
    	log_msg(LOG_ERROR, "Window creation failed!\n");

    	return 1;
    }

    KeyInputStore& kis = KeyInputStore::getInstance();
    log_msg(LOG_DEBUG, "kis: %p\n", &kis);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, KeyInputStore::keyCallback);

    if (!setupGLEW()) return 1;

    glClearColor(0.5, 0.5, 0.8, 1.0);

    log_msg(LOG_INFO, "Starting up test...\n");
    log_msg(LOG_DEBUG, "GLFW_KEY_ESCAPE: %d\n", GLFW_KEY_ESCAPE);
    while (!glfwWindowShouldClose(window)) {
    	//log_msg(LOG_DEBUG, "Looping...\n");
    	//log_msg(LOG_DEBUG, "kis.numKeys = %d\n", kis.numKeys);
    	int state = kis.getState(GLFW_KEY_ESCAPE);
    	//log_msg(LOG_DEBUG, "kis.numKeys = %d\n", kis.numKeys);
    	//log_msg(LOG_DEBUG, "state: %d\n", state);
    	if (state == GLFW_PRESS) {
    		glfwTerminate();
    		return 0;
    	}

    	glClear(GL_COLOR_BUFFER_BIT);

    	glfwPollEvents();
    	glfwSwapBuffers(window);
    }

    glfwTerminate();
	return 0;
}