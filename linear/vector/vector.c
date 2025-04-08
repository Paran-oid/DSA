#include <vector.h>

#include <stdlib.h>

void vector_create(Vector* vec, size_t el_size, void (*destroy)(void*), void (*match)(const void*, const void*))
{
    vec->el_size = el_size;
    vec->destroy = destroy;
    vec->capacity = CAPACITY_INIT;
    vec->size = 0;
    vec->items = calloc(CAPACITY_INIT, el_size);
    vec->match = match;
}
void vector_destroy(Vector* vec);

int vector_get(Vector* vec, size_t index, void** out);
int vector_set(Vector* vec, size_t index, void* data);

int vector_pushback(Vector* vec, void* data);
int vector_pop(Vector* vec, void** data);

int vector_resize(Vector* vec, size_t new_capacity);
int vector_clear(Vector* vec);
int vector_find(Vector* vec, void* data);