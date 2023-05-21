// Program to convert a vowel into uppercase
#include <stdio.h>
#include <string.h>
int main()
{
	printf("Enter a string using underscore in place of space \n");
	char s[100], c;
	scanf("%s", &s);
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == 'a')
		{
			s[i] = 'A';
		}
		else if (s[i] == 'e')
		{
			s[i] = 'E';
		}
		else if (s[i] == 'i')
		{
			s[i] = 'I';
		}
		else if (s[i] == 'o')
		{
			s[i] = 'O';
		}
		else if (s[i] == 'u')
		{
			s[i] = 'U';
		}
		else
		{
			s[i] = s[i];
		}
		c = s[i];
		printf("%c", c);
	}
}