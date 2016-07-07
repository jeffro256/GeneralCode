#pragma once

#include <GLFW/glfw3.h>

class KeyListener {
public:
    virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    bool isAlive() { return alive; }
    void kill() { alive = false; }
    
private:
    bool alive = true;
};

void addKeyListener(KeyListener* listener);
void listenerKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
