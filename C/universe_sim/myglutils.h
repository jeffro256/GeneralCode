#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int setupGLFW();
int setupGLEW();
void setupCoreGL();

GLchar* shaderError(GLuint shader);
GLchar* programError(GLuint program);
GLuint getProgram(const char* vs, const char* fs);
GLuint getProgramFromFiles(const char* vsFileName, const char* fsFileName);
