#include <stdio.h>

unsigned int ack(unsigned int m, unsigned int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return ack(m - 1, 1);
    else return ack(m - 1, ack(m, n - 1));
}

int main() {
    int m = 4, n = 2;

    printf("ack(%d, %d) == %d\n", m, n, ack(m, n));

    return 0;
}
