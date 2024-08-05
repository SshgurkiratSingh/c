#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stddef.h>  // For size_t
#include <stdint.h>  // For uint8_t
#include <stdbool.h> // For bool

#define MAX_BUFFER_ENTRIES 10

// Structure representing an entry in the circular buffer
struct circular_buffer_entry
{
    const char *data;
    size_t size;
};

// Structure representing the circular buffer
struct circular_buffer
{
    struct circular_buffer_entry entries[MAX_BUFFER_ENTRIES];
    uint8_t write_index;
    uint8_t read_index;
    bool full;
};

// Function prototypes
void circular_buffer_init(struct circular_buffer *buffer);
void circular_buffer_add_entry(struct circular_buffer *buffer, const char *data, size_t size);
struct circular_buffer_entry *circular_buffer_find_entry(struct circular_buffer *buffer, size_t offset);
bool circular_buffer_is_full(struct circular_buffer *buffer);
bool circular_buffer_is_empty(struct circular_buffer *buffer);
void circular_buffer_free(struct circular_buffer *buffer);
struct circular_buffer_entry *display_current_buffer(struct circular_buffer *buffer, bool printfIt);

#endif /* CIRCULAR_BUFFER_H */
