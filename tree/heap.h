#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct Heap_ {
    size_t size;
    void (*destroy)(void* data);
    int (*match)(const void* key1, const void* key2);
    void** tree;
} Heap;

void heap_create(Heap* heap, int (*match)(const void* key1, const void* key2),
    void (*destroy)(void* data));
void heap_destroy(Heap* heap);
int heap_insert(Heap* heap, const void* data);
int heap_extract(Heap* heap, void** data);

#define heap_size(heap) ((heap)->size)

#endif