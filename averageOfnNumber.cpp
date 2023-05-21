// Program to find the average of n numbers
#include <stdio.h>
int main()
{
	int n;
	printf("Enter number of elements:");
	scanf("%d", &n);
	float arr[n];
	float sum = 0;
	printf("Enter the elements:");
	for (int i = 0; i < n; i++)
	{
		scanf("%f", &arr[i]);
		sum += arr[i];
	}
	printf("The array is:");
	for (int i = 0; i < n; i++)
	{
		printf("%f", arr[i]);
	}
	printf("\nThe average is %f", sum / n);
}