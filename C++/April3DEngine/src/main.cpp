#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_help.h"

#include <cstdlib>
#include <cstdio>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_RATIO ((float) WINDOW_WIDTH / WINDOW_HEIGHT)

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

static glm::vec3 camPos(2, 1.5, -1);
static glm::vec3 lightPos(2, 2, 2);
static glm::mat4 view_projection_matrix;
static glm::mat4 model_matrix(1.0);
static glm::mat4 normal_transfrom_matrix(1.0);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_info), cube_info, GL_STATIC_DRAW);

	GLint sprogram = getProgramFromFiles("res/shaders/phong_notexture.vs.glsl",
										 "res/shaders/phong_notexture.fs.glsl");

	GLint viewproj_location = glGetAttribLocation(sprogram, "view_projection_matrix");
	GLint model_location = glGetAttribLocation(sprogram, "model_matrix");
	GLint normtrans_location = glGetAttribLocation(sprogram, "normal_transfrom_matrix");
	GLint pos_location = glGetAttribLocation(sprogram, "model_pos");
	GLint normal_location = glGetAttribLocation(sprogram, "model_normal");
	GLint color_location = glGetAttribLocation(sprogram, "model_color");

	if (viewproj_location < 0) {
		std::fputs("Could not get 'view_projection_matrix' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (model_location < 0) {
		std::fputs("Could not get 'model_matrix' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (normtrans_location < 0) {
		std::fputs("Could not get 'normal_transfrom_matrix' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (pos_location < 0) {
		std::fputs("Could not get 'model_pos' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (normal_location < 0) {
		std::fputs("Could not get 'model_normal' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	if (color_location < 0) {
		std::fputs("Could not get 'model_color' location in shader program\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glm::mat4 projection = glm::prespective(4.5, WINDOW_RATIO, 0.1, 100.0);
	glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0, 0.0, 0.0, glm::vec3(0.0, 1.0, 0.0)));
	view_projection_matrix = projection * view;

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
