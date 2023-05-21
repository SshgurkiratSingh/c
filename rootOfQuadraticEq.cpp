// Program to find the roots of a quadratic equation
#include <stdio.h>
#include <math.h>
int main()

{
	int a, b, c, d, root1, root2;
	printf("Enter the coefficients of eqution(ax^2+bx+c):\n");
	scanf("%d %d %d", &a, &b, &c);
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		root1 = (-b + sqrt(d)) / (2 * a);
		root2 = (-b - sqrt(d)) / (2 * a);
		printf("Root 1:%d\n", root1);
		printf("Root 2:%d\n", root2);
	}
	else
	{
		printf("no real roots\n");
	}
	return 0;
}
