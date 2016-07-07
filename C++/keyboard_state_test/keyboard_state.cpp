#include <logger.h> // TEMPORARY!!!!!
#include <stdlib.h>

#include "keyboard_state.hpp"

#define BITS_IN_INT (sizeof(int) * 8)

KeyboardState::KeyboardState(int numKeys) {
    keys = NULL;
    reserve(numKeys);
    
    addKeyListener(this);
    log_msg(LOG_DEBUG, "this->numKeys(construct): %d\n", this->numKeys);
}

KeyboardState::KeyboardState() {
    KeyboardState::KeyboardState(256);
}

void KeyboardState::keyPressed(int key) {
    if (key >= numKeys) {
        reserve(key + 1);
    }
    
    keys[key / BITS_IN_INT] |= 1 << (key % BITS_IN_INT);
}

void KeyboardState::keyReleased(int key) {
    if (key >= numKeys) {
        reserve(key + 1);
    }
    
    keys[key / BITS_IN_INT] &= ~(1 << (key % BITS_IN_INT));
}

void KeyboardState::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyPressed(key);
    }
    else if (action == GLFW_RELEASE) {
        keyReleased(key);
    }
}

int KeyboardState::getKeyState(int key) {
    log_msg(LOG_DEBUG, "this->numKeys: %d\n", this->numKeys);
    if (key >= numKeys) {
        reserve(key + 1);
        return false;
    }
    
    const int keyIndex = key / BITS_IN_INT;
    const int bitOffset = key % BITS_IN_INT;
    return (keys[keyIndex] & (1 << bitOffset)) >> bitOffset;
}

void KeyboardState::clear() {
    for (int i = 0; i < numKeys / BITS_IN_INT; i++) {
        keys[i] = 0;
    }
}

void KeyboardState::reserve(int numKeys) {
    if (numKeys % BITS_IN_INT != 0) {
        numKeys += BITS_IN_INT - numKeys % BITS_IN_INT;
    }
    else {
        numKeys += BITS_IN_INT;
    }

    const int bytesToAlloc = numKeys / BITS_IN_INT;
    keys = (int*) malloc(bytesToAlloc);
    this->numKeys = numKeys;
    clear();
}
