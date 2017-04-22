#include <glad/glad.h>
#include "GLBufferObjects.hpp"

template <std::size_t N>
GLBufferObjects<N>::GLBufferObjects() {
	glGenBuffers(numObjs, objects.data());
}

template <std::size_t N>
GLBufferObjects<N>::~GLBufferObjects() {
	glDeleteBuffers(numObjs, objects.data());
}

template <std::size_t N>
GLuint GLBufferObjects<N>::get(int index) {
	return objects[index];
}

template <std::size_t N>
void GLBufferObjects<N>::bind(int index, GLenum target) {
	glBindBuffer(target, objects[index]);
}

template <std::size_t N>
void GLBufferObjects<N>::buffer(
		int index,
		GLsizeiptr size, 
		const GLvoid* data, 
		GLenum usage, 
		GLenum target) {
	bind(index, target);
	glBufferData(target, size, data, usage);
}