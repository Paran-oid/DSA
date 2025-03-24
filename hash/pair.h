#ifndef PAIR_H
#define PAIR_H

#include <stddef.h>

typedef struct Pair_ {
    void* key;
    void* val;

    void (*destroy)(void*);

    size_t key_size;
    size_t val_size;
} Pair;

void pair_create(Pair* p, void (*destroy)(void*), size_t key_size, size_t val_size);
void pair_destroy(Pair* p);

int pair_set(Pair* p, const void* key, const void* val);

#define pair_key(p) ((p)->key)
#define pair_val(p) ((p)->val)

#endif