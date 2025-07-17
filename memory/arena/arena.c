#include "arena.h"

#include <stdlib.h>
#include <string.h>

void arena_create(Arena* arena, size_t capacity)
{
    arena->capacity = capacity;
    arena->size = 0;
    arena->data = malloc(capacity);

    if (!arena->data) {
        arena->capacity = 0;
    }
}
void arena_destroy(Arena* arena)
{
    free(arena->data);
    memset(arena, 0, sizeof(Arena));
}
int arena_allocate(Arena* arena, size_t elsize, void** data)
{
    if (arena_remaining(arena) == 0) {
        return -1;
    }

    *data = (unsigned char*)arena->data + arena->size;
    arena->size += elsize;

    return 0;
}

int arena_clear(Arena* arena)
{
    arena->size = 0;
    memset(arena->data, 0, arena->capacity);
    return 0;
}

int arena_reset(Arena* arena)
{
    arena->size = 0;
    return 0;
}

size_t arena_used(Arena* arena)
{
    return arena->size;
}

size_t arena_remaining(Arena* arena)
{
    return arena->capacity - arena->size;
}
