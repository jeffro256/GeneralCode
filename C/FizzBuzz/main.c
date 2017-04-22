#include <stdio.h>
#include <time.h>

#define TIMEDTEST(x, c) {                                           \
    clock_t old = clock();                                          \
                                                                    \
    for (int i = 0; i < c; i++) {                                   \
        x;                                                          \
    }                                                               \
                                                                    \
    clock_t new = clock();                                          \
    float elapsed = (float) (new - old) / CLOCKS_PER_SEC;           \
    printf("'%s' did %d loops in %f seconds.\n", #x, c, elapsed);   \
}

#define TIMEDTESTF(x, c, f) {                                           \
    clock_t old = clock();                                          \
                                                                    \
    for (int i = 0; i < c; i++) {                                   \
        x;                                                          \
    }                                                               \
                                                                    \
    clock_t new = clock();                                          \
    float elapsed = (float) (new - old) / CLOCKS_PER_SEC;           \
    fprintf(f, "'%s' did %d loops in %f seconds.\n", #x, c, elapsed);   \
}

void fizzbuzz();

void fizzbuzz_control() {
    for (int i = 1; i <= 100; i++) {
        if (!(i % 15))
            printf ("FizzBuzz");
        else if (!(i % 3))
            printf ("Fizz");
        else if (!(i % 5))
            printf ("Buzz");
        else
            printf ("%d", i);
 
        printf("\n");
    }
}

int main() {
    FILE* f = fopen("results.txt", "r+");

    TIMEDTESTF(fizzbuzz(), 1000, f);
    TIMEDTESTF(fizzbuzz_control(), 1000, f);


    char buffer[4096];
    rewind(f);
    buffer[fread(buffer, 1, sizeof(buffer) - 1, f)] = '\0';
    printf("%s", buffer);

    return 0;
}
