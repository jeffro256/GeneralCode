#include "logger.h"
#include "myglutils.h"

#include <stdlib.h>
#include <string.h>

static void glfwErrorCallback(int error, const char* description);
static int getIntsFromString(const char* stringPtr, int ints[]);
static int getFloatsFromString(const char* stringPtr, float floats[]);

#ifdef __WIN32__
#include "getline.h"
#endif

int setupGLFW() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        log_msg(LOG_ERROR, "GLFW3 initialization failed.\n");

        return 0;
    }

    return 1;
}

int setupGLEW() {
    glewExperimental = GL_TRUE;
    GLenum glewErr;

    if ((glewErr = glewInit()) != GLEW_OK) {
        log_msg(LOG_ERROR, "%s\n", glewGetErrorString(glewErr));
        log_msg(LOG_ERROR, "GLEW initialization failed.\n");

        return 0;
    }

    return 1;
}

void setupCoreGL() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLchar* shaderError(GLuint shader) {
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE) {
        GLint maxLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);
        
        GLchar* errorLog = (GLchar*) malloc(maxLen);
        glGetShaderInfoLog(shader, maxLen, &maxLen, errorLog);

        return errorLog;
    }

    return NULL;
}

GLchar* programError(GLuint program) {
    GLint isLinked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE) {
        GLint maxLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);

        GLchar* errorLog = (GLchar*) malloc(maxLen);
        glGetProgramInfoLog(program, maxLen, &maxLen, errorLog);

        return errorLog;
    }

    GLint isValidated = GL_FALSE;
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &isValidated);

    if (isValidated == GL_FALSE) {
        GLint maxLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);

        GLchar* errorLog = (GLchar*) malloc(maxLen);
        glGetProgramInfoLog(program, maxLen, &maxLen, errorLog);

        return errorLog;
    }

    return NULL;
}

GLuint getProgram(const char* vertexShader, const char* fragmentShader) {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);

    if (!vs) {
        log_msg(LOG_WARNING, "Error creating vertex shader");

        return 0;
    }

    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);

    GLchar* error;
    if ((error = shaderError(vs)) != NULL) {
        log_msg(LOG_WARNING, "Error compiling vertex shader:\n%s\n", error);
        
        glDeleteShader(vs);
        
        return 0;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    if (!fs) {
        log_msg(LOG_WARNING, "Error creating fragment shader");

        glDeleteShader(vs);
        
        return 0;
    }

    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);

    if ((error = shaderError(fs)) != NULL) {
        log_msg(LOG_WARNING, "Error compiling fragment shader:\n%s\n", error);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
        
        return 0;
    }

    GLuint program = glCreateProgram();

    if (!program) {
        log_msg(LOG_WARNING, "Error creating program");

        glDeleteShader(vs);
        glDeleteShader(fs);

        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    if ((error = programError(program)) != NULL) {
        log_msg(LOG_WARNING, "Error linking/validating program:\n%s\n", error);
        
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        
        return 0;
    }
    
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint getProgramFromFiles(const char* vsFileName, const char* fsFileName) {
    FILE* vsFile = fopen(vsFileName, "r");
    FILE* fsFile = fopen(fsFileName, "r");
    
    if (vsFile == NULL) {
        log_msg(LOG_WARNING, "getProgramFromFiles() could not open vertex shader file "
                             "'%s'!\n", vsFileName);
        
        if (fsFile != NULL) {
            fclose(fsFile);
        }
        
        return 0;
    }
    else if (fsFile == NULL) {
        log_msg(LOG_WARNING, "getProgramFromFiles() could not open fragment shader file "
                             "'%s'!\n", fsFileName);
        
        if (vsFile != NULL) {
            fclose(vsFile);
        }
        
        return 0;
    }
    
    size_t pos = ftell(vsFile);
    fseek(vsFile, 0, SEEK_END);
    const size_t vsFileLen = ftell(vsFile);
    fseek(vsFile, pos, SEEK_SET);

    pos = ftell(fsFile);
    fseek(fsFile, 0, SEEK_END);      
    const size_t fsFileLen = ftell(fsFile);                           
    fseek(fsFile, pos, SEEK_SET);

    char vsSource[vsFileLen + 1];
    char fsSource[fsFileLen + 1];

    fread(vsSource, vsFileLen, 1, vsFile);
    fread(fsSource, fsFileLen, 1, fsFile);
    
    fclose(vsFile);
    fclose(fsFile);
    
    vsSource[vsFileLen] = '\0';
    fsSource[fsFileLen] = '\0';

    return getProgram(vsSource, fsSource);
}

// STATIC HELPER FUNCTIONS

#define NUMS_ON_LINE 3

static void glfwErrorCallback(int error, const char* description) {
    log_msg(LOG_ERROR, "ERROR CODE %d:\n", error);
    log_msg(LOG_ERROR, "%s\n", description);
}

static int getIntsFromString(const char* stringPtr, int ints[]) {
    char* string = (char*) stringPtr;
    char* end;

    for (int i = 0; i < NUMS_ON_LINE; i++) {
        int num = (int) strtol(string, &end, 10);

        if (end == stringPtr) {
            log_msg(LOG_WARNING, "Problem reading line: %s\n", stringPtr);

            return 0;
        }

        ints[i] = num;
        string = end;
    }
    
    return 1;
}

static int getFloatsFromString(const char* stringPtr, float floats[]) {
    char* string = (char*) stringPtr;
    char* end;

    for (int i = 0; i < NUMS_ON_LINE; i++) {
        float num = strtof(string, &end);

        if (end == stringPtr) {
            log_msg(LOG_WARNING, "Problem reading line: %s\n", stringPtr);

            return 0;
        }

        floats[i] = num;
        string = end;
    }
    
    return 1;
}
