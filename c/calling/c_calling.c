// Look at this file's assembly output

#include <stddef.h>

void lprint(const char*, size_t);

int main() {
    const char testString[7] = "Hello!\n";

    lprint(testString, sizeof(testString));

    return 0;
}
