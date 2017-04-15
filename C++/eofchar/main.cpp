#include <stdio.h> 
int main(void)
{
    int letter;
    printf("Write a string.I will repeat it until EOF.\n");
    while ((letter = getchar()) != EOF)
    {
        printf("%c", letter);
    }
    printf("EOF received. Code %d\n", letter);
    return 0;

}
