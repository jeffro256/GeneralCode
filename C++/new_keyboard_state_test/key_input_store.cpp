#include "key_input_store.hpp"
#include <cstdlib>

int KeyInputStore::getState(int key) {
	if (key >= this->numKeys) {
		reserve(key + 1);
	}

	return states[key];
}

KeyInputStore::KeyInputStore() {
	reserve(256);
}

KeyInputStore& KeyInputStore::getInstance() {
	static KeyInputStore instance;

	return instance;
}

void KeyInputStore::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	KeyInputStore kis = getInstance();

	if (key >= kis.numKeys) {
		kis.reserve(key + 1);
	}

	kis.states[key] = action;
}

void KeyInputStore::reserve(int numKeys) {
	if (this->states != NULL) {
		free(states);
	}

	this->states = (char*) std::malloc(numKeys);
	this->numKeys = numKeys;
}