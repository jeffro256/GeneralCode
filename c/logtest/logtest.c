#include <stdio.h>
#include <stdlib.h>

#include <logger.h>

int main(int argc, char* argv[]) {
    int log_num;
    
    if (argc > 1) {
        log_num = atoi(argv[1]);
    }
    else {
        log_num = 100;
    }
    
    set_log_file(fopen("lol.log", "w"));
    for (int i = 0; i < log_num; i++) {
        log_msg(LOG_INFO, "%d\n", i);
    }
    
    return 0;
}