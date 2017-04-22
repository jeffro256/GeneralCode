#include <glad/glad.h>
#include "shader_help.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

GLchar* programLinkError(GLuint program) {
    GLint isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE) {
        GLint maxLen;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);

        GLchar* errorLog = (GLchar*) malloc(maxLen);
        glGetProgramInfoLog(program, maxLen, &maxLen, errorLog);

        return errorLog;
    }

    return NULL;
}

GLchar* programValidationError(GLuint program) {
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
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);

    GLchar* error;
    if ((error = shaderError(vs)) != NULL) {
        fprintf(stderr, "Error compiling vertex shader:\n%s\n", error);
        
        glDeleteShader(vs);

        free(error);        

        return 0;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);

    if ((error = shaderError(fs)) != NULL) {
        fprintf(stderr, "Error compiling fragment shader:\n%s\n", error);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
        
        free(error);

        return 0;
    }

    GLuint program = glCreateProgram();

    if (!program) {
        fputs("Error creating program shader!", stderr);
        
        glDeleteShader(vs);
        glDeleteShader(fs);

        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    if ((error = programLinkError(program)) != NULL) {
        fprintf(stderr, "Error linking/validating program:\n%s\n", error);
        
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);

        free(error);

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
        fprintf(stderr, "getProgramFromFiles() could not open vertex shader file "
                             "'%s'!\n", vsFileName);
        
        if (fsFile != NULL) {
            fclose(fsFile);
        }
        
        return 0;
    }
    else if (fsFile == NULL) {
        fprintf(stderr, "getProgramFromFiles() could not open fragment shader file "
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

int getMultipleAttribLocations(GLuint program, int numAttribs, const char* const* names, GLint* locations) {
    int badLoc = numAttribs;

    for (int i = 0; i < numAttribs; i++) {
        GLint location = glGetAttribLocation(program, names[i]);

        locations[i] = location;

        if (location < 0) {
            badLoc = i;
        }
    }

    return badLoc;
}

int getMultipleUniformLocations(GLuint program, int numUniforms, const char* const* names, GLint* locations) {
    int badLoc = numUniforms;

    for (int i = 0; i < numUniforms; i++) {
        GLint location = glGetUniformLocation(program, names[i]);

        locations[i] = location;

        if (location < 0) {
            badLoc = i;
        }
    }

    return badLoc;
}
