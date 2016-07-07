#pragma once

#include "key_listener.hpp"

class KeyboardState: public KeyListener {
    public:
        KeyboardState(int numKeys);
        KeyboardState();
    
        void keyPressed(int key);
        void keyReleased(int key);
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
        int getKeyState(int key);
        void clear();
        
    //private: // REMOVE COMMENT AFTER DEBUGGING
        int numKeys;
        int* keys;
        
        void reserve(int numKeys);
};