#include "circular_buffer.h"
#include <string.h> // For memcpy

// Initializes the circular buffer
void circular_buffer_init(struct circular_buffer *buffer)
{
    buffer->full = false;
    buffer->write_index = 0;
    buffer->read_index = 0;
}

// Adds an entry to the circular buffer
void circular_buffer_add_entry(struct circular_buffer *buffer, const char *data, size_t size)
{
    struct circular_buffer_entry *entry = &buffer->entries[buffer->write_index];
    entry->data = data;
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
