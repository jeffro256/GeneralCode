#ifndef __MYGLUTILS__
#define __MYGLUTILS__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

int setupGLFW();
int setupGLEW();

#ifdef __APPLE__
void setupApple();
#endif

GLchar* shaderError(GLuint shader);
GLchar* programError(GLuint program);
GLuint getProgram(const char* vs, const char* fs);
GLuint getProgramFromFiles(const char* vsFileName, const char* fsFileName);
GLuint loadBMP(const char* fileName);
int loadWavefront1(const char* fileName, float** vertexBuffer, int* length);

#ifdef __cplusplus
}
#endif
#endif
