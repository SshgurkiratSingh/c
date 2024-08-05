#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy
#include <time.h>   // For time and ctime

// Initializes the circular buffer
void circular_buffer_init(struct circular_buffer *buffer)
{
    buffer->full = false;
    buffer->write_index = 0;
    buffer->read_index = 0;
    for (uint8_t i = 0; i < MAX_BUFFER_ENTRIES; i++)
    {
        buffer->entries[i].data = NULL;
        buffer->entries[i].size = 0;
    }
}

// Adds an entry to the circular buffer
void circular_buffer_add_entry(struct circular_buffer *buffer, const char *data, size_t size)
{
    struct circular_buffer_entry *entry = &buffer->entries[buffer->write_index];
    if (entry->data != NULL)
    {
        free((void *)entry->data);
    }
    entry->data = (char *)malloc(size);
    memcpy(entry->data, data, size);
    entry->size = size;
    buffer->write_index = (buffer->write_index + 1) % MAX_BUFFER_ENTRIES;

    // TODO: Add new data entry, update write index, handle wrap-around, and manage full status
    if (circular_buffer_is_full(buffer))
    {
        buffer->read_index = (buffer->read_index + 1) % MAX_BUFFER_ENTRIES;
    }
    buffer->full = (buffer->write_index == buffer->read_index);
}

// Finds an entry in the circular buffer by offset
struct circular_buffer_entry *circular_buffer_find_entry(struct circular_buffer *buffer, size_t offset)
{
    if (circular_buffer_is_empty(buffer))
    {
        return NULL;
    }
    size_t totalRead = 0;
    uint8_t currentIndex = buffer->read_index;

    while (totalRead < offset)
    {
        totalRead += buffer->entries[currentIndex].size;
        if (totalRead >= offset)
        {
            return &buffer->entries[currentIndex];
        }
        currentIndex = (currentIndex + 1) % MAX_BUFFER_ENTRIES;
    }

    return NULL;
}

// Checks if the circular buffer is full
bool circular_buffer_is_full(struct circular_buffer *buffer)
{
    return buffer->full;
}

// Checks if the circular buffer is empty
bool circular_buffer_is_empty(struct circular_buffer *buffer)
{
    return (!buffer->full && (buffer->write_index == buffer->read_index));
}
void circular_buffer_free(struct circular_buffer *buffer)
{
    // TODO: Free the circular buffer
    for (uint8_t i = 0; i < MAX_BUFFER_ENTRIES; i++)
    {
        if (buffer->entries[i].data != NULL)
        {
            free((void *)buffer->entries[i].data);
            buffer->entries[i].data = NULL;
            buffer->entries[i].size = 0;
        }
    }
}

struct circular_buffer_entry *display_current_buffer(struct circular_buffer *buffer, bool printfIt)
{
    uint8_t index = buffer->read_index;

    if (buffer->read_index == buffer->write_index)
    {
        return NULL;
    }
    if (printfIt)
    {
        printf("Current buffer:\n");

        char *data = (char *)malloc(buffer->entries[index].size);
        memcpy(data, (char *)buffer->entries[index].data, buffer->entries[index].size);
        printf("Data: %s, Size: %zu\n", data, buffer->entries[index].size);
        free((void *)data);
    }
    return &buffer->entries[index];
}