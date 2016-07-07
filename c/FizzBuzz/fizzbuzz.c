#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static const char fizz[4] = "Fizz";
static const char buzz[4] = "Buzz";
static char fizzbuzz_print_buffer[413];

void fizzbuzz() {
    unsigned int buffIndex = 0;

    for (unsigned int i = 1; i < 100; i++) {
        bool divisbleBy3 = false;

        if (i % 3 == 0) {
            strncpy(&fizzbuzz_print_buffer[buffIndex], fizz, sizeof(fizz));
            buffIndex += sizeof(fizz);
            divisbleBy3 = true;
        }

        if (i % 5 == 0) {
            strncpy(&fizzbuzz_print_buffer[buffIndex], buzz, sizeof(buzz));
            buffIndex += sizeof(buzz);
        }
        else if (!divisbleBy3) {
            if (i >= 10) {
                fizzbuzz_print_buffer[buffIndex++] = '0' + (i / 10) % 10;
            }

            fizzbuzz_print_buffer[buffIndex++] = '0' + i % 10;
        }

        fizzbuzz_print_buffer[buffIndex++] = '\n';
    }

    strncpy(&fizzbuzz_print_buffer[buffIndex], buzz, sizeof(buzz));
    buffIndex += sizeof(buzz);
    fizzbuzz_print_buffer[buffIndex++] = '\n';

    fwrite(fizzbuzz_print_buffer, 1, sizeof(fizzbuzz_print_buffer), stdout);
}
