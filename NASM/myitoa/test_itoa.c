#include <stdio.h>

char* itoa(char* buffer, int num);

int main() {
	char buff[12];

    char* res = itoa(buff, -999999);
    printf("buff: %p\n", buff);
    printf("res: %p\n", res);
    printf("res - buff: %ld\n", res - buff);
	printf("%s\n", res);

	return 0;
}