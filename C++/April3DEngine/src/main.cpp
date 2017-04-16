#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_help.h"

#include <cstdlib>
#include <cstdio>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static void glfw_error_callback(int error, const char* description) {
	std::fprintf(stderr, "Error (%d): %s\n", error, description);
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static const GLfloat vert_info[] = {
	 0.0,  0.8, 1.0, 0.0, 0.0,
	 0.7, -0.4, 0.0, 1.0, 0.0,
	-0.7, -0.4, 0.0, 0.0, 1.0,
};

// Formattted like so: x, y, z, nx, ny, nz, r, g, b
static const GLfloat cube_info[] = {
	-1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	 1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	-1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	-1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	 1.0, -1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	 1.0,  1.0,  1.0,  0.0,  0.0,  1.0, 0.027, 0.459, 1.000,
	 1.0, -1.0,  1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0, -1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0,  1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0,  1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0, -1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0, -1.0,  1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	-1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	 1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	 1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	-1.0, -1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	-1.0,  1.0, -1.0,  0.0,  0.0, -1.0, 0.027, 0.459, 1.000,
	-1.0, -1.0, -1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0, -1.0,  1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0, -1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0, -1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0, -1.0,  1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0,  1.0, -1.0,  0.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	-1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0,  1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0,  1.0, -1.0,  0.0,  1.0,  0.0, 0.027, 0.459, 1.000,
	-1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
	-1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0, -1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
	 1.0, -1.0,  1.0,  0.0, -1.0,  0.0, 0.027, 0.459, 1.000,
};

static const char* vshader_src = "#version 330 core\n"
"in vec2 pos;\n"
"in vec3 vcolor;\n"
"out vec3 color;\n"
"void main() {\n"
"    gl_Position = vec4(pos, 0.0, 1.0);\n"
"    color = vcolor;\n"
"}\n";

static const char* fshader_src = "#version 330 core\n"
"in vec3 color;\n"
"out vec3 fcolor;\n"
"void main() {\n"
"    fcolor = color;\n"
"}\n";

int main() {
	GLFWwindow* window;

	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit()) {
		std::fputs("Could not initialize GLFW!\n", stderr);
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "April3D", NULL, NULL);
	if (!window) {
		std::fputs("Could not create a GLFW window!\n", stderr);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::fputs("GLAD failed to load OpenGL\n", stderr);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	printf("OpenGL Version (GLAD): %d.%d\n", GLVersion.major, GLVersion.minor);

	glClearColor(0.25, 0.25, 0.25, 1.0);

	GLuint vert_info_buffer;
	glGenBuffers(1, &vert_info_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vert_info_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_info), vert_info, GL_STATIC_DRAW);

	GLint sprogram = getProgram(vshader_src, fshader_src);

	GLint vertex_location = glGetAttribLocation(sprogram, "pos");
	GLint color_location = glGetAttribLocation(sprogram, "vcolor");

	if (vertex_location < 0) {
		std::fputs("Could not get 'pos' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (color_location < 0) {
		std::fputs("Could not get 'color' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(vertex_location, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*) (sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(vertex_location);
	glEnableVertexAttribArray(color_location);

	GLchar* validErrMsg;
	if ((validErrMsg = programValidationError(sprogram))) {
		fprintf(stderr, "%s\n", validErrMsg);

		free(validErrMsg);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	} 

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(sprogram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vert_info_buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(sprogram);
	glfwTerminate();

	return EXIT_SUCCESS;
}
