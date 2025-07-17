#include <vector.h>

#include <stdlib.h>
#include <string.h>

void vector_create(Vector* vec, size_t el_size, void (*destroy)(void*), int (*match)(const void*, const void*))
{
    vec->items = calloc(CAPACITY_INIT, sizeof(void*));
    if (!vec->items) {
        exit(EXIT_FAILURE);
    }

    vec->el_size = el_size;
    vec->capacity = CAPACITY_INIT;
    vec->size = 0;

    vec->match = match;
    vec->destroy = destroy;
}
void vector_destroy(Vector* vec)
{
    if (vec->destroy) {
        for (size_t i = 0; i < vec->size; i += vec->el_size) {
            vec->destroy(vec->items[i]);
        }
    }
    free(vec->items);
}

int vector_get(Vector* vec, size_t index, void** out)
{
    if (index >= vec->size) {
        return -1;
    }
    *out = vec->items[index];
    return 0;
}
int vector_set(Vector* vec, size_t index, void* data)
{
    if (index >= vec->size) {
        return -1;
    }
    memcpy(vec->items[index], data, vec->el_size);
    return 0;
}

int vector_pushback(Vector* vec, void* data)
{
    if (vec->size == vec->capacity) {
        vector_resize(vec, vec->capacity * 2);
    }

    vec->items[vec->size] = malloc(vec->el_size);
    if (!vec->items[vec->size]) {
        return -1;
    }

    memcpy(vec->items[vec->size], data, vec->el_size);
    vec->size++;
    return 0;
}
int vector_pop(Vector* vec, void** data)
{
    if (vec->size == 0) {
        return 1;
    }
    memcpy(*data, vec->items[vec->size - 1], vec->el_size);
    vec->size--;
    return 0;
}

int vector_resize(Vector* vec, size_t new_capacity)
{
    void** new_items = realloc(vec->items, new_capacity);
    vec->capacity = new_capacity;
    vec->items = new_items;
    return 0;
}
int vector_find(Vector* vec, void* data)
{
    for (size_t i = 0; i < vec->size; i += vec->el_size) {
        if (vec->match(vec->items[i], data)) {
            return (int)i;
        }
    }
    return -1;
}
