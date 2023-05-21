/* This Program finds the repeated characters in the string */
#include <stdio.h>
#include <string.h>
int main()
{
	printf("Enter a string using underscore in place of space \n");
	char s[100], ch;
	int i, rep = 0;
	scanf("%s", &s);
	strlwr(s);
	printf("Repeated characters are : \n");
	for (i = 0; s[i] != '\0'; i++)
	{
		for (int j = i + 1; s[j] != '\0'; j++)
			if (s[i] == s[j])
			{
				ch = s[i];
				printf("%c\t", ch);
				rep++;
			}
	}
	printf("\nNo. of repeated characters are\t%d", rep);
}