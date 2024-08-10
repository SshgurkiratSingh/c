#include <time.h>
#include <stdio.h>

void writeTimeStampToFile()
{
    // get current time in a variable
    time_t t = time(NULL);
    char str[80];
    // convert time to rfc2822 format
    strftime(str, sizeof(str), "%a, %d %b %Y %H:%M:%S %z", localtime(&t));
    printf("Current time: %s\n", str);
}

int main()
{
    writeTimeStampToFile();
    return 0;
}