#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* itoa(char*, int);

#define LOOP_COUNT 100000000L

// x is statement to run
#define TIMEDTEST(x, c) \
    old = clock(); \
    for (long i = 0; i < c; i++) { \
        x; \
    } \
    new = clock(); \
    elapsed = (float) (new - old) / CLOCKS_PER_SEC; \
    printf("'%s' did %ld loops in %f seconds.\n", #x, c, elapsed);

static uint16_t const str100p[100] = {
    0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830, 0x3930, 
    0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731, 0x3831, 0x3931, 
    0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732, 0x3832, 0x3932, 
    0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733, 0x3833, 0x3933, 
    0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734, 0x3834, 0x3934, 
    0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935, 
    0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936, 
    0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937, 
    0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938, 
    0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839, 0x3939,
};

char *itoa_vitaut(char *buf, uint32_t val) {
    char *p = &buf[10];
    *p = '\0';

    while (val >= 100) {
        const uint32_t old = val;

        p -= 2;
        val /= 100;
        *((uint16_t*) p) = str100p[old - (val * 100)];
    }

    p -= 2;
    *((uint16_t*) p) = str100p[val];

    return &p[val < 10];
}

char *itoa_vitaut_2(char *buf, int val) {
    char *p = &buf[10];
    bool issigned = val < 0;
    *p = '\0';

    if (issigned) val *= -1;

    while (val >= 100) {
        const int old = val;

        p -= 2;
        val /= 100;
        *((uint16_t*) p) = str100p[old - (val * 100)];
    }

    p -= 2;
    *((uint16_t*) p) = str100p[val];

    if (issigned) (--p)[val < 10] = '-';

    return &p[val < 10];
}

char* itoa_vitaut_3(char *buf, int32_t val) {
    char *p = &buf[10];
    const bool issigned = val < 0;
    *p = '\0';

    if (issigned) val *= -1;

    while (val >= 100) {
        const int32_t old = val;

        p -= 2;
        val /= 100;
        *((uint16_t*) p) = str100p[old - (val * 100)];
    }

    p -= 2;
    *((uint16_t*) p) = str100p[val];

    if (issigned) (--p)[val < 10] = '-';

    return &p[val < 10];
}

char* itoa_vitaut_4(char *buf, int32_t val) {
    char* p = &buf[11];
    const bool issigned = val < 0;
    *p = '\0';

    if (issigned) val *= -1;

    while ((uint32_t) val >= 100U) {
        const uint32_t old = val;

        p -= 2;
        val /= (uint32_t) 100U;
        *((uint16_t*) p) = str100p[old - ((uint32_t) val * 100U)];
    }

    p -= 2;
    *((uint16_t*) p) = str100p[(uint32_t) val];

    if (issigned) (--p)[(uint32_t) val < 10U] = '-';

    return &p[(uint32_t) val < 10U];
}

char* itoa_vitaut_5(char* buf, int val) {
    static const unsigned int max_size = sizeof(int) == 2 ? 7 : 12;

    char* p = &buf[max_size];
    const bool issigned = val < 0;
    
    *p = '\0';
    
    if (issigned) val *= -1;

    while ((unsigned int) val >= 100U) {
        const unsigned int old = val;

        p -= 2;
        val /= (unsigned int) 100U;
        *((uint16_t*) p) = str100p[old - ((unsigned int) val * 100U)];
    }

    p -= 2;
    *((uint16_t*) p) = str100p[(unsigned int) val];

    if (issigned) (--p)[(unsigned int) val < 10U] = '-';

    return &p[(unsigned int) val < 10U];
}

int main() {
    char buffer[20];
    clock_t old, new;
    float elapsed;
    
    srand(time(NULL));

    //TIMEDTEST(snprintf(buffer, sizeof(buffer), "%d", rand()), LOOP_COUNT);
    //TIMEDTEST(itoa_vitaut(buffer, rand()), LOOP_COUNT);
    //TIMEDTEST(itoa_vitaut_2(buffer, rand()), LOOP_COUNT);
    //TIMEDTEST(itoa_vitaut_3(buffer, rand()), LOOP_COUNT);
    TIMEDTEST(itoa_vitaut_4(buffer, rand()), LOOP_COUNT);
    TIMEDTEST(itoa_vitaut_5(buffer, rand()), LOOP_COUNT);
    TIMEDTEST(itoa(buffer, rand()), LOOP_COUNT);

    /*for (int i = -1020; i <= 1020; i++) {
        puts(itoa_vitaut_2(buffer, i));
    }*/

    return 0;
}
