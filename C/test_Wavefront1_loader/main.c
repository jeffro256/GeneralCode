#include <logger.h>
#include <myglutils.h>
#include <stdlib.h>

int main() {
    float* vertices;
    int length;    

    const char* path = "/Users/jeffaryan/Code/c/test_Wavefront1_loader/cube.obj";
    if (!loadWavefront1(path, &vertices, &length)) {
        log_msg(LOG_ERROR, "Loading object file '%s' failed.\n", path);

        return 1; 
    }

    for (int i = 0; i < length / 3; i++) {
        printf("%f %f %f\n", vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
    }

    free(vertices);

    return 0;
}
