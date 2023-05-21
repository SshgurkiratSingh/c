// Program  to count vowels and consonants in a string
#include <stdio.h>
#include <string.h>
int main()
{
	printf("Enter a string using underscore in place of space \n");
	char str[100], ch;
	int i, vow = 0, con = 0;
	scanf("%s", &str);
	strlwr(str);
	for (i = 0; str[i] != '\0'; i++)
	{
		ch = str[i];
		if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
		{
			vow++;
		}
		else
		{
			con++;
		}
	}
	printf("No. of Vowels are\t%d", vow);
	printf("\n No. of Consonants are\t%d ", con);
}