/*
	Program to sort the numbers in ascending order
*/
#include <stdio.h>
int main()
{
	int i, j, a, n, number[200];
	printf("Enter the value of N\n");
	scanf("%d", &n);
	printf("enter the number\n");
	for (i = 0; i < n; i++)
		scanf("%d", &number[i]);
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; ++j)
		{
			if (number[i] > number[j])
			{
				a = number[i];
				number[i] = number[j];
				number[j] = a;
			}
		}
	}
	printf("the numbers arranged in ascending order :\n");
	for (i = 0; i < n; i++)
		printf("%d\n", number[i]);
	return 0;
}