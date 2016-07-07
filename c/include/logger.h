#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_DEBUG   0
#define LOG_INFO    1
#define LOG_WARNING 2
#define LOG_ERROR   3

void set_log_file(FILE* file);
void setDebug(int shouldDebug);
void setBind(int shouldBind);
void log_msg(const int log_type, const char* message, ...) __printflike(2, 3);

#ifdef __cplusplus
}
#endif

#endif
