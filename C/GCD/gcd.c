int gcd(int a, int b) {
    int c;

    while (a != 0) {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}