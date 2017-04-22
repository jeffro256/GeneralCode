#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <logger.h>

static const char* log_tags[] = {
    " [DEBUG] ",
    " [INFO] ",
    " [WARNING] ",
    " [ERROR] "
};

static FILE* log_file = NULL;
static int debug = 0;
static int bind = 0;

void set_log_file(FILE* file) {
    log_file = file;
}

void setDebug(int shouldDebug) {
    debug = shouldDebug;
}

void setBind(int shouldBind) {
    bind = shouldBind;
}

void log_msg(const int log_type, const char* message, ...) {
    if (!debug && log_type == LOG_DEBUG) return;

    if (log_file == NULL) {
        set_log_file(stdout);
    }
    
    const char* log_tag;
    if (log_type < 0 || log_type >= sizeof(log_tags)) {
        log_tag = "UNKNOWN";
    }
    else {
        log_tag = log_tags[log_type];
    }
    
    // PRINT TIME STRING
    char time_str[128];
    time_t now = time(NULL);
    struct tm* loctime = localtime(&now);
    strftime(time_str, 128, "%d/%m/%Y %H:%M:%S", loctime);
    
    fprintf(log_file, "%s", time_str);
    fprintf(log_file, "%s", log_tag);
    
    
    if (bind && log_file != stdout && log_file != stderr) {
        if (log_type == LOG_ERROR) {
            fprintf(stderr, "%s", time_str);
            fprintf(stderr, "%s", log_tag);
        }
        else {
            fprintf(stdout, "%s", time_str);
            fprintf(stdout, "%s", log_tag);
        }
    }
    
    //PRINT MESSAGE
    va_list arg_ptr;
    va_start(arg_ptr, message);
    vfprintf(log_file, message, arg_ptr);
    va_end(arg_ptr);
    
    va_start(arg_ptr, message);
    if (bind) {
        if (log_type == LOG_ERROR) {
            vfprintf(stderr, message, arg_ptr);
        }
        else {
            vfprintf(stdout, message, arg_ptr);
        }
    }
    va_end(arg_ptr);
    
    fflush(log_file);
    fflush(stdout);
    fflush(stderr);
}
