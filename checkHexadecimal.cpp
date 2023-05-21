// Program to check whether a character is a hexadecimal digit or not
#include <stdio.h>
#include <ctype.h>
int main()
{
	char c;
	printf("enter a character:\n");
	scanf("%s", &c);
	if (isxdigit(c))
	{
		printf("It is a hexadecimal digit");
	}
	else
	{
		printf("It is not a hexadecimal digit");
	}
}
