#include <stdio.h>

int main() {
    int a = 1000000001;
    float b = (int) a;
    int c = a - (int) b;

    puts("Not a whole lot going on here, just testing how accurate 32-bit floats can store the number one billion and one.");
    printf("Original int: %d\n", a);
    printf("32-bit float version: %f\n", b);
    printf("Int difference (should be zero): %d\n", c);

    return 0;
}
