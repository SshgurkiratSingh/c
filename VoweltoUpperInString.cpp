// Program to convert a vowel into uppercase
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    printf("Enter a string using underscores in place of spaces: \n");
    char s[100];
    scanf("%s", s);

    for (int i = 0; i < strlen(s); i++) {
        switch (tolower(s[i])) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                s[i] = toupper(s[i]);
                break;
            default:
                break;
        }
        printf("%c", s[i]);
    }

    return 0;
}
