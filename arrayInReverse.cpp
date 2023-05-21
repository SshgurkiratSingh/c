/* Program to read n number of values in an array and display it in reverse order.
 */
#include <stdio.h>
int main()
{
	int n;
	printf(" Enter number of elements:");
	scanf("%d", &n);
	int arr[n];
	float sum = 0;
	printf("Enter the elements:");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf(" The final array is:");
	for (int i = n - 1; i >= 0; i--)
	{
		printf("%d", arr[i]);
	}
}