#include <myglutils.h>

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <logger.h>

static void glfwErrorCallback(int error, const char* description);
static int getIntsFromString(const char* stringPtr, int ints[]);
static int getFloatsFromString(const char* stringPtr, float floats[]);

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
        log_msg(LOG_ERROR, "%s\n", glewGetString(glewErr));
        log_msg(LOG_ERROR, "GLEW initialization failed.\n");

        return 0;
    }

    return 1;
}

void setupApple() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);

    GLchar* error;
    if ((error = shaderError(vs)) != NULL) {
        log_msg(LOG_WARNING, "Error compiling vertex shader:\n%s\n", error);
        
        glDeleteShader(vs);
        
        return 0;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);

    if ((error = shaderError(fs)) != NULL) {
        log_msg(LOG_WARNING, "Error compiling fragment shader:\n%s\n", error);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
        
        return 0;
    }

    GLuint program = glCreateProgram();
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

GLuint loadBMP(const char* fileName) {
    FILE* file = fopen(fileName, "rb");
    
    if (file == NULL) {
        log_msg(LOG_WARNING, "File '%s' could not be opened.\n", fileName);
    
        return 0;
    }
    
    char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    
    if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') {
        log_msg(LOG_WARNING, "File '%s' is not formated correctly.\n", fileName);
        
        return 0;
    }
    
    dataPos = *((int*) &(header[0x0A]));
    imageSize = *((int*) &(header[0x22]));
    width = *((int*) &(header[0x12]));
    height = *((int*) &(header[0x16]));
    
    if (!imageSize) imageSize = width * height * 3;
    if (!dataPos) dataPos = 54;
    
    char data[54 + imageSize];
    strcpy(data, header);
    fread(data + 54, 1, imageSize, file);
    
    fclose(file);
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data + dataPos);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return texture;
}

int loadWavefront1(const char* fileName, float** vertexBuffer, int* length) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        log_msg(LOG_WARNING, "Cannot open file '%s'.\n", fileName);
        
        return 0;
    }
    
    int vertices = 0;
    int faces = 0;
    char* line = NULL;
    size_t l; // ONLY HERE BECAUSE getline() wants it
    
    while (getline(&line, &l, file) != -1) {
        if (line[0] == 'v' && line[1] == ' ') {
            vertices++;
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            faces++;
        }
    }
    
    //free(line);
    fseek(file, 0, SEEK_SET);
    
    float coordsRaw[vertices * 3];
    int faceVertices[faces * 3];
    int vertex = 0;
    int face = 0;
    
    while (getline(&line, &l, file) != -1) {
        if (!line) {
            log_msg(LOG_WARNING, "Line is null.\n");
        }
        
        if (line[0] == 'v' && line[1] == ' ') {
            if (!getFloatsFromString(&line[2], &coordsRaw[vertex * 3])) {
                log_msg(LOG_WARNING, "Cannot parse vertex string '%s'\n", line);
            }
            
            vertex++;
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            if (!getIntsFromString(&line[2], &faceVertices[face * 3])) {
                log_msg(LOG_WARNING, "Cannot parse face string: '%s'\n", line);
            }
            
            face++;
        }
    }
    
    free(line);
    fclose(file);
    
    *length = faces * 9;
    *vertexBuffer = (float*) malloc(faces * 9 * sizeof(float));
    
    for (int face = 0; face < faces; face++) {
        for (int vertex = 0; vertex < 3; vertex++) {
            int vertexIndex = faceVertices[face * 3 + vertex] - 1;
            
            for (int coord = 0; coord < 3; coord++) {
                (*vertexBuffer)[face * 9 + vertex * 3 + coord] = coordsRaw[vertexIndex * 3 + coord];
            }
        }
    }
    
    return 1;
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
