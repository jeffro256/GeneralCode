#include <stdio.h>

int main() {
    const char* a = "HaHaHa!!!";
    const char* b = "HaHaHa!!!";
    char* c = "HaHaHa!!!"; // not const
    const char d[] = "HaHaHa!!!"; // an array
    char e[] = "HaHaHa!!!"; // an non-const array

    puts("The point of this is to see whether the compiler shares string literals");
    printf("*a = %s\n", a);
    printf("a: %p\n", a);
    printf("b: %p\n", b);
    printf("c: %p\n", c);
    printf("d: %p\n", d);
    printf("e: %p\n", e);
    printf("a == b: %d\n", a == b);
    printf("a == c: %d\n", a == c);
    printf("a == d: %d\n", a == d);
    printf("a == e: %d\n", a == e);
    printf("d == e: %d\n", (char*) d == (char*) e);
    puts("Writing to c (type char*) produces a Bus Error");
    puts("However, writing to e (type char[]) is fine!");
    puts("Attemping to write to d...");
    e[1] = e[3] = e[5] = 'o';
    printf("*d = %s\n", d);
    puts("Attemping to write to c...");
    c[1] = c[3] = c[5] = 'o';
    printf("*c = %s\n", c); // this line never gets executed because of the bus error

    return 0;
}
