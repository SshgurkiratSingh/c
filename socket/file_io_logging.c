#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>


#define FILE_PATH "/home/gurkirat/Projects/c/socket/file_io_logging.txt"
#define BUFFER_SIZE 1024

void write_to_file(const char *data)
{
    FILE *f = fopen(FILE_PATH, "a");
    if (f == NULL)
    {
        syslog(LOG_ERR, "Error opening file: %s", strerror(errno));
        exit(1);
    }
    fprintf(f, "%s\n", data);
    fclose(f);
    // TODO: Implement file writing logic
}

void read_from_file()
{
    FILE *f = fopen(FILE_PATH, "r");
    if (f == NULL)
    {
        syslog(LOG_ERR, "Error opening file: %s", strerror(errno));
        exit(1);
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, f) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(f);
    // TODO: Implement file reading logic
}

void delete_file()
{
    if (remove(FILE_PATH) == 0)
    {
        syslog(LOG_INFO, "Successfully deleted file");
    }
    else
    {
        syslog(LOG_ERR, "Failed to delete file: %s", strerror(errno));
    }
}

int main()
{
    // TODO: Initialize syslog
    openlog("file_io_logging", LOG_CONS, LOG_USER);
    openlog("file_io_logging", LOG_PID | LOG_CONS, LOG_USER);

    // Call write_to_file
    const char *data = "This is a test message for file I/O operations with logging.";
    write_to_file(data);

    // Call read_from_file
    read_from_file();

    // Call delete_file
    delete_file();

    // Clean up and close syslog
    closelog();

      return 0;
}