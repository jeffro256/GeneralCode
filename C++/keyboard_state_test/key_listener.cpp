#include <logger.h> // TEMPORARY
#include <vector>

#include "key_listener.hpp"

static std::vector<KeyListener*> listeners;

void addKeyListener(KeyListener* listener) {
    listeners.push_back(listener);
}

void listenerKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (int i = 0; i < listeners.size(); i++) {
        KeyListener* listener = listeners[i];
        
        if (listener->isAlive()) {
            listener->keyCallback(window, key, scancode, action, mods);
        }
    }
}