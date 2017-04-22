#include <stdio.h>

int get_secret_num() {
    static int secret = -10;

    if (secret == -10) {
        secret = 0;
    }

    return secret++;
}

int main() {
    for (int _ = 0; _ < 5; _++) {
        printf("Secret num: %d\n", get_secret_num());
    }

    return 0;
}
