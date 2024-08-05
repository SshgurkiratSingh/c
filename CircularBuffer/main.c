#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "circular_buffer.h"

#define MAX_MESSAGE_LENGTH 256

enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

struct LogMessage {
    enum LogLevel level;
    time_t timestamp;
    char message[MAX_MESSAGE_LENGTH];
};

void log_message(struct circular_buffer *buffer, enum LogLevel level, const char *message) {
    struct LogMessage log_entry;
    log_entry.level = level;
    log_entry.timestamp = time(NULL);
    strncpy(log_entry.message, message, MAX_MESSAGE_LENGTH - 1);
    log_entry.message[MAX_MESSAGE_LENGTH - 1] = '\0';

    circular_buffer_add_entry(buffer, (const char *)&log_entry, sizeof(struct LogMessage));
}

void display_logs(struct circular_buffer *buffer, int count) {
    printf("Recent logs (up to %d):\n", count);
    int displayed = 0;
    uint8_t index = buffer->read_index;

    while (displayed < count && !circular_buffer_is_empty(buffer)) {
        struct circular_buffer_entry *entry = &buffer->entries[index];
        if (entry->data != NULL) {
            struct LogMessage *log = (struct LogMessage *)entry->data;
            char *level_str;
            switch (log->level) {
                case INFO: level_str = "INFO"; break;
                case WARNING: level_str = "WARNING"; break;
                case ERROR: level_str = "ERROR"; break;
            }
            char time_str[26];
            ctime_r(&log->timestamp, time_str);
            time_str[24] = '\0';  // Remove newline
            printf("[%s] %s: %s\n", time_str, level_str, log->message);
            displayed++;
        }
        index = (index + 1) % MAX_BUFFER_ENTRIES;
        if (index == buffer->write_index) break;
    }
}

void search_logs(struct circular_buffer *buffer, const char *keyword) {
    printf("Searching for logs containing '%s':\n", keyword);
    uint8_t index = buffer->read_index;

    while (!circular_buffer_is_empty(buffer)) {
        struct circular_buffer_entry *entry = &buffer->entries[index];
        if (entry->data != NULL) {
            struct LogMessage *log = (struct LogMessage *)entry->data;
            if (strstr(log->message, keyword) != NULL) {
                char *level_str;
                switch (log->level) {
                    case INFO: level_str = "INFO"; break;
                    case WARNING: level_str = "WARNING"; break;
                    case ERROR: level_str = "ERROR"; break;
                }
                char time_str[26];
                ctime_r(&log->timestamp, time_str);
                time_str[24] = '\0';  // Remove newline
                printf("[%s] %s: %s\n", time_str, level_str, log->message);
            }
        }
        index = (index + 1) % MAX_BUFFER_ENTRIES;
        if (index == buffer->write_index) break;
    }
}

int main() {
    struct circular_buffer log_buffer;
    circular_buffer_init(&log_buffer);

    // Log some messages
    log_message(&log_buffer, INFO, "Application started");
    log_message(&log_buffer, WARNING, "Low memory warning");
    log_message(&log_buffer, ERROR, "Failed to connect to database");
    log_message(&log_buffer, INFO, "User logged in: John Doe");
    log_message(&log_buffer, INFO, "Processing data");
    log_message(&log_buffer, WARNING, "Slow network connection detected");
    log_message(&log_buffer, ERROR, "Unexpected data format");
    log_message(&log_buffer, INFO, "Data processing completed");
    log_message(&log_buffer, INFO, "User logged out: John Doe");
    log_message(&log_buffer, INFO, "Application shutdown initiated");
    log_message(&log_buffer, INFO, "Application stopped");

    // Display recent logs
    display_logs(&log_buffer, 5);

    printf("\n");

    // Search for logs containing a keyword
    search_logs(&log_buffer, "User");

    // Free the circular buffer
    circular_buffer_free(&log_buffer);

    return 0;
}