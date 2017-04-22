#include <stdio.h>

unsigned long collatz(unsigned long n) {
    unsigned long times = 0;

    while (n != 1) {
        if (n & 1) {
            n = 3 * n + 1;
        }
        else {
            n = n << 1;
        }

        times++;
    }

    return times;
}

int main() {
    unsigned long n = 3;

    printf("collatz(%lu) == %lu\n", n, collatz(n));

    return 0;
}
