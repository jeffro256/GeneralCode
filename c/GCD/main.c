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

int gcd_subtract(int num1, int num2) {
    while (num1 != num2) {
        if (num1 > num2) {
            num1 -= num2;
        }
        else {
            num2 -= num1;
        }
    }

    return num1;
}

int gcd_mod(int a, int b) {
    int c;

    while (a != 0) {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}

int main() {
    int a, b;
    const int times = 100000000;

    scanf("%d %d", &a, &b);

    printf("Timing...\r");
    fflush(stdout);

    TIMEDTEST(gcd_subtract(a, b), times);
    TIMEDTEST(gcd_mod(a, b), times);

    return 0;
}
