#ifndef PATH_HELPER_H
#define PATH_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

void updateProgramPath(const char* cmdarg0);
const char* getProgramFolder();
const char* getProgramFile();
const char* getFullProgramPath();
char* rap(const char* path);

#ifdef __cplusplus
}
#endif
#endif