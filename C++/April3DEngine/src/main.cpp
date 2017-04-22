#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_help.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_RATIO ((float) WINDOW_WIDTH / WINDOW_HEIGHT)

#define LEN(a) sizeof(a) / sizeof(a[0])

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

static glm::vec3 camPos(2.8, 1.5, 6);
static glm::vec3 lightPos(2.4, 2, 4);
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

	glfwWindowHint(GLFW_SAMPLES, 4);
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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.25, 0.25, 0.25, 1.0);
	glClearDepth(1.0);

	GLuint vert_info_buffer;
	glGenBuffers(1, &vert_info_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vert_info_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_info), cube_info, GL_STATIC_DRAW);

	GLint sprogram = getProgramFromFiles("res/shaders/phong_notexture.vs.glsl",
										 "res/shaders/phong_notexture.fs.glsl");
	
	if (!sprogram) {
		std::fputs("Could not make a GLSL shader program!\n", stderr);
		glDeleteBuffers(1, &vert_info_buffer);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	const char* uniform_names[] = {
		"view_projection_matrix",
		"model_matrix",
		"normal_transform_matrix",
		"light_pos",
		"light_color",
		"eye_pos"
	};
	const int num_uniforms = LEN(uniform_names);
	GLint uniform_locations[num_uniforms];
	int badLoc;
	if ((badLoc = getMultipleUniformLocations(sprogram, num_uniforms, 
											  uniform_names, uniform_locations)) != num_uniforms) {
		std::fprintf(stderr, "Could not get uniform location of '%s'!\n", uniform_names[badLoc]);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}
	for (int i = 0; i < num_uniforms; i++) {
		if (uniform_locations[i] < 0) {
			std::fprintf(stderr, "Could not get uniform location of '%s'!\n", uniform_names[i]);
			glDeleteBuffers(1, &vert_info_buffer);
			glDeleteProgram(sprogram);
			glfwTerminate();
			return EXIT_FAILURE;
		}
	}

	const char* attrib_names[] = {
		"model_pos",
		"model_normal",
		"model_color"
	};
	const int num_attribs = LEN(attrib_names);
	GLint attrib_locations[num_attribs];
	if ((badLoc = getMultipleAttribLocations(sprogram, num_attribs, 
												 attrib_names, attrib_locations)) != num_attribs) {
		std::fprintf(stderr, "Could not get attribute location of '%s'!\n", attrib_names[badLoc]);
		glDeleteBuffers(1, &vert_info_buffer);
		glDeleteProgram(sprogram);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	GLint viewproj_location		= uniform_locations[0];
	GLint model_location		= uniform_locations[1];
	GLint normtrans_location	= uniform_locations[2];
	GLint lightpos_location		= uniform_locations[3];
	GLint lightcolor_location	= uniform_locations[4];
	GLint campos_location		= uniform_locations[5];
	
	GLint pos_location			= attrib_locations[0];
	GLint normal_location		= attrib_locations[1];
	GLint color_location		= attrib_locations[2];

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), WINDOW_RATIO, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	view_projection_matrix = projection * view;

	glUseProgram(sprogram);
	glUniformMatrix4fv(viewproj_location, 1, GL_FALSE, &view_projection_matrix[0][0]);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &model_matrix[0][0]);
	glUniformMatrix4fv(normtrans_location, 1, GL_FALSE, &normal_transfrom_matrix[0][0]);

	glUniform3f(lightpos_location, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(lightcolor_location, 1.0, 1.0, 1.0);
	glUniform3f(campos_location, camPos.x, camPos.y, camPos.z);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(pos_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, NULL);
	glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*) (sizeof(GLfloat) * 3)); 
	glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*) (sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(pos_location);
	glEnableVertexAttribArray(normal_location);
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
		std::clock_t old_time = std::clock();
		///////////////////////////////////////////////////
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(sprogram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
		///////////////////////////////////////////////////
		std::clock_t new_time = std::clock();
		float elapsed = (float) (new_time - old_time) / CLOCKS_PER_SEC;
		float fps = 1 / elapsed;
		std::printf("FPS: %f\r", fps);
	}

	std::puts("");

	glDeleteBuffers(1, &vert_info_buffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(sprogram);
	glfwTerminate();

	return EXIT_SUCCESS;
}
