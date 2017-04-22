#include <glad/glad.h>
#include "GLVertexArrays.hpp"

template <std::size_t N>
GLVertexArrays<N>::GLVertexArrays() {
    glGenVertexArrays(numArrays, arrays.data());
}

template <std::size_t N>
GLVertexArrays<N>::~GLVertexArrays() {
    glDeleteVertexArrays(numArrays, arrays.data());
}

template <std::size_t N>
GLuint GLVertexArrays<N>::get(int index) {
    return arrays[index];
}

template <std::size_t N>
void GLVertexArrays<N>::bind(int index) {
    glBindVertexArray(arrays[index]);
}