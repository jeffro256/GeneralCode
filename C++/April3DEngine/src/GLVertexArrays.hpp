#ifndef _GL_VERTEX_ARRAYS_HPP_
#define _GL_VERTEX_ARRAYS_HPP_

#include <array>

#ifndef GL_VERSION_1_0
#error "No OpenGL headers included"
#endif

template<std::size_t N>
class GLVertexArrays {
public:
	static constexpr std::size_t numArrays = N;

	GLVertexArrays();
	~GLVertexArrays();

	GLuint get(int index);

	void bind(int index);
private:
	std::array<GLuint, N> arrays;
};

#endif