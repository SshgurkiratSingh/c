// PRogram to calculate age
#include <stdio.h>
#include <time.h>
int main()
{
	int birth_year, birth_month, birth_day;
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	printf("enter your date of birth(YYYY-MM-DD):");
	scanf("%d-%d-%d", &birth_year, &birth_month, &birth_day);
	int age_years = current_time->tm_year + 1900 - birth_year;
	int age_months = current_time->tm_mon + 1 - birth_month;
	int age_days = current_time->tm_mday - birth_day;
	if (age_days < 0)
	{
		age_months--;
		age_days += 30; 
	}
	if (age_months < 0)
	{
		age_years--;
		age_months += 12;
	}
	printf("you are %d years,%d months,and %d days old.\n", age_years, age_months, age_days);
}
