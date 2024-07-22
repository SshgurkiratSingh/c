/* This program converts the entered string to lowercase */
#include <stdio.h>
#include <string.h>
int main(void)
{
	printf("Enter a string using underscore in place of space:");
	char str[100], up[100];
	int i;
	scanf("%s", &str);
	printf("%s", strlwr(str));
}
