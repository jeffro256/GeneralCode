#ifndef __MYGLUTILS__
#define __MYGLUTILS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int setupGLFW();
int setupGLEW();

#ifdef __APPLE__
void setupApple();
#endif

GLuint getShader(const char* vs, const char* fs);
#endif
