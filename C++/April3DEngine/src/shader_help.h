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

#ifdef __cplusplus
}
#endif
#endif
