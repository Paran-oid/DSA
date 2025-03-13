#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Pair_ {
    void* key;
    void* value;

    size_t key_size;
    size_t value_size;
} Pair;

#define ASSERT(_e, ...)                   \
    do {                                  \
        if (!(_e)) {                      \
            fprintf(stderr, __VA_ARGS__); \
            exit(EXIT_FAILURE);           \
        }                                 \
    } while (0)

void swap(void* key1, void* key2, size_t item_size);

#endif