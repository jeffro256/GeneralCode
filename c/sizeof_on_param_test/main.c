#include <stdio.h>
#include <stdlib.h>

int sizetest(int[]);

int main() {
    int a1[] = { 42, 69, 2 };
    int a2[] = { 0, 100, 9 };

    printf("Size of array one: %d\n", sizetest(a1));
    printf("Size of array two: %d\n", sizetest(a2));

    return 0;
}

int sizetest(int array[]) {
    return sizeof(array);
}
