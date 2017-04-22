#ifndef __MYGLUTILS__
#define __MYGLUTILS__

#ifdef __cplusplus
extern "C" {
#endif

GLchar* shaderError(GLuint shader);
GLchar* programLinkError(GLuint program);
GLchar* programValidationError(GLuint program);

GLuint getProgram(const char* vs, const char* fs);
GLuint getProgramFromFiles(const char* vsFileName, const char* fsFileName);

// returns index of first error, length of array if successful, but does all regardless
int getMultipleAttribLocations(GLuint program, int numAttribs, const char* const* names, GLint* locations);
int getMultipleUniformLocations(GLuint program, int numUniforms, const char* const* names, GLint* locations);

#ifdef __cplusplus
}
#endif
#endif
