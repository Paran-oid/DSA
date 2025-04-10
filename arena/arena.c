#include "arena.h"

#include <stdlib.h>

void arena_create(Arena* arena, size_t capacity, void (*destroy)(const void* item))
{
    arena->capacity = capacity;
    arena->size = capacity;
    arena->destroy = destroy;
    arena->data = malloc(capacity);
}
void arena_destroy(Arena* arena)
{
}
int arena_allocate(Arena* arena, size_t elsize)
{
}
int arena_deallocate(Arena* arena, void* ptr)
{
}
