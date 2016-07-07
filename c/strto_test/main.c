#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: strto_test string\n");

        return 1;
    }

    char* end;

    printf("End raw before: %p\n", end);    

    float number = strtof(argv[1], &end);

    printf("Got number: %f\n", number);
    printf("End ptr: %s\n", end);
    printf("String raw: %p\n", argv[1]);
    printf("End raw after: %p\n", end);
    printf("End minus String: %ld\n", end - argv[1]);

    return 0;
}
