#include <path_helper.h>
#include <stdlib.h>
#include <string.h>

static char* programFolder = NULL;
static char* programFile = NULL;
static char* fullPath = NULL;

void updateProgramPath(const char* cmdarg0) {
    int argLen = strlen(cmdarg0);
    
    for (int i = argLen; i >= 0; i--) {
        if (cmdarg0[i] == '/') {
            char* mutablePath = strdup(cmdarg0);
            mutablePath[i] = '\0';
            
            programFolder = (char*) malloc(i + 1);
            strcpy(programFolder, mutablePath);
            
            programFile = (char*) malloc(argLen - i);
            strcpy(programFile, &mutablePath[i + 1]);
            
            fullPath = (char*) malloc(argLen + 1);
            strcpy(fullPath, cmdarg0);
            
            free(mutablePath);
            
            break;
        }
    }
}

const char* getProgramFolder() {
    return (const char*) programFolder;
}

const char* getProgramFile() {
    return (const char*) programFile;
}

const char* getFullProgramPath() {
    return (const char*) fullPath;
}

// Stands for "relative to absolute path"
char* rap(const char* path) {
    char* returnPath = (char*) malloc(strlen(programFolder) + strlen(path) + 2);
    
    strcpy(returnPath, programFolder);
    strcat(returnPath, "/");
    strcat(returnPath, path);
    
    return returnPath;
}