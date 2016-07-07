#include <stdbool.h>
#include <stdio.h>

#define IAMDUCK 0

bool hasthelargehadroncolliderdestroyedtheworldyet() {
    return false;
}

bool aminotaduck() {
    return !IAMDUCK;
}

int shoulddonaldtrumpbepresident() {
    return false;
}

bool trueAsAnInt() {
    return true;
}

int main() {
    printf("%d\n", hasthelargehadroncolliderdestroyedtheworldyet());
    printf("%d\n", aminotaduck());
    printf("%d\n", shoulddonaldtrumpbepresident());
    printf("%d\n", trueAsAnInt() + 1);

    return 0;
}
