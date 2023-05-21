// Program to find sum of first n natural number and print all digit
#include <stdio.h>
int main()
{
	int n, i, sum = 0;
	printf("enter the value of n");
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
	{
		printf("\t%d", i);
		sum = sum + i;
	}
	printf("\tsum of first n natural number is %d", sum);
}