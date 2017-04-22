#ifndef _GL_BUFFER_OBJECTS_HPP_
#define _GL_BUFFER_OBJECTS_HPP_

#include <array>

#ifndef GL_VERSION_1_0
#error "No OpenGL headers included"
#endif

template<std::size_t N>
class GLBufferObjects {
public:
	static constexpr std::size_t numObjs = N;

	GLBufferObjects();
	~GLBufferObjects();

	GLuint get(int index);

	void bind(int index, GLenum target = GL_ARRAY_BUFFER);
	void buffer(
		int index,
		GLsizeiptr size, 
		const GLvoid* data, 
		GLenum usage = GL_STATIC_DRAW, 
		GLenum target = GL_ARRAY_BUFFER);
private:
	std::array<GLuint, N> objects;
};

#endif