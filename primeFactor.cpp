/* this program is to print all prime factors of a given number.

*/
#include <stdio.h>
int main()
{
	int a, n, i, b;
	printf("enter a number:");
	scanf("%d", &n);
	printf("list of prime factors of %d\n", n);
	for (a = 2; a < +n; a++)
	{
		if (n % a == 0)
		{
			b = 1;
			for (i = 2; i <= (a / 2); i++)
			{
				if (a % i == 0)
				{
					b = 0;
					break;
				}
			}
			if (b == 1)
				printf("%d\t", a);
		}
	}
	return 0;
}