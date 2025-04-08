#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define CAPACITY_INIT 100

typedef struct Vector_ {
    void* items;

    void (*match)(const void*, const void*);
    void (*destroy)(void*);

    size_t el_size;
    size_t size;
    size_t capacity;
} Vector;

void vector_create(Vector* vec, size_t el_size, void (*destroy)(void*), void (*match)(const void*, const void*));
void vector_destroy(Vector* vec);

int vector_get(Vector* vec, size_t index, void** out);
int vector_set(Vector* vec, size_t index, void* data);

int vector_pushback(Vector* vec, void* data);
int vector_pop(Vector* vec, void** data);

int vector_resize(Vector* vec, size_t new_capacity);
int vector_clear(Vector* vec);
int vector_find(Vector* vec, void* data);

#define vector_size(vec) ((vec)->size)
#define vector_capacity(vec) ((vec)->capacity)

#endif