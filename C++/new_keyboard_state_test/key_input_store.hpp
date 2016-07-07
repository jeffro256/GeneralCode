#pragma once

#include <GLFW/glfw3.h>

// Singleton class for getting keyboard input
class KeyInputStore {
	public:
		int getState(int key);

		static KeyInputStore& getInstance();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	//private:
		char* states = NULL;
		int numKeys;

		KeyInputStore();
		void reserve(int numKeys);

		// Uncomment when g++ is better!!!
		//KeyInputStore(KeyInputStore const&)   = delete;
        //void operator=(KeyInputStore const&)  = delete;
};