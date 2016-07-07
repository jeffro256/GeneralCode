#include <stdio.h>

int main() {
    const int my_array[] = {0, 1, 2, 3, 4};
    const int cool_num = 2;
    const int* my_pointer = &cool_num;

    printf("%p\n", &my_array);
    printf("%p\n", &my_pointer);
    printf("%p\n", &my_array[0]);
    printf("%p\n", &my_pointer[0]);

    return 0;
}
