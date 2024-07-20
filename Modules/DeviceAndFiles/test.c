#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
    int fd = open("/dev/myDev", O_RDONLY);

    if (fd < 0)
    {
        printf("Error opening file: %s\n", strerror(errno));
        exit(1);
    }
    else
    {
        printf("File opened successfully. File descriptor: %d\n", fd);
    }

    if (close(fd) < 0)
    {
        printf("Error closing file: %s\n", strerror(errno));
        exit(1);
    }

    printf("File closed successfully\n");
    return 0;
}