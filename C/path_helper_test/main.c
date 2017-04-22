#include <path_helper.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    updateProgramPath(argv[0]);

    printf("Command Line Argument 0: %s\n", argv[0]);
    printf("Current Relative Folder: %s\n", getProgramFolder());

    const char* path = "testfile.txt";
    printf("File path: %s\n", path);

    const char* newPath = rap(path);
    printf("New path: %s\n", newPath);

    printf("Opening file...\n");

    FILE* file = fopen(newPath, "r");
    if (file == NULL) {
        printf("Oh noes! Opening the file failed!!! ;(\n");

        return 1;
    }

    char buffer[256];
    while (fgets(buffer, 256, file) != NULL) {
        printf("%s", buffer);
    }

    puts("");

    return 0;
}
