#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena_ {
    void* data;

    size_t size;
    size_t capacity;
} Arena;

void arena_create(Arena* arena, size_t capacity);
void arena_destroy(Arena* arena);

int arena_allocate(Arena* arena, size_t elsize, void** data);
int arena_clear(Arena* arena);
int arena_reset(Arena* arena);

size_t arena_used(Arena* arena);
size_t arena_remaining(Arena* arena);

#define arena_size(area) ((area)->size)
#define arena_capacity(area) ((area)->capacity)

#endif
