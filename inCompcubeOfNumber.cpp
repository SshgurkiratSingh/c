//Program to print the cube of the given number
#include <stdio.h>
int main()
{
	int i, n;
	printf("enter the number:");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		printf("cube of the %d is:%d\n", i, (i * i * i));
	}
	return 0;
}