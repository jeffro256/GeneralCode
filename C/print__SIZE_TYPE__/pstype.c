#include <stdio.h>

#define MSTR(s) STR(s)
#define STR(s) #s

int main() {
    printf("__SIZE_TYPE__ is defined as %s\n", MSTR(__SIZE_TYPE__));
    printf("Its size is %lu\n", sizeof(__SIZE_TYPE__));

    return 0;
}
