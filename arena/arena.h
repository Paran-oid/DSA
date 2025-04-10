#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena_ {
    void* data;

    void (*destroy)(const void* item);

    size_t size;
    size_t capacity;
} Arena;

void arena_create(Arena* arena, size_t capacity, void (*destroy)(const void* item));
void arena_destroy(Arena* arena);

int arena_allocate(Arena* arena, size_t elsize);
int arena_deallocate(Arena* arena, void* ptr);

#define arena_size(area) ((area)->size)
#define arena_capacity(area) ((area)->capacity)

#endif
