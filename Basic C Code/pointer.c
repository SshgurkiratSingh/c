#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    FILE *f = fopen("nd.txt", "r");
    fseek(f, 0, SEEK_END);
    int n = ftell(f);
    char c = fgetc(f);
    printf("%c", c);
    fclose(f);
}
