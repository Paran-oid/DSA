#include "pair.h"

#include <stdlib.h>
#include <string.h>

void pair_create(Pair* p, void (*destroy)(void*), size_t key_size, size_t val_size)
{
    p->key = NULL;
    p->val = NULL;
    p->key_size = key_size;
    p->val_size = val_size;
    p->destroy = destroy;
}
void pair_destroy(Pair* p)
{
    if (p->destroy) {
        p->destroy(p->key);
        p->destroy(p->val);
    }
    p->key = NULL;
    p->val = NULL;
    memset(p, 0, sizeof(Pair));
}

int pair_set(Pair* p, const void* key, const void* val)
{
    if (!key || !val) {
        return -1;
    }

    p->key = malloc(p->key_size);

    if (!p->key) {
        return -1;
    }

    p->val = malloc(p->val_size);
    if (!p->val) {
        free(p->key);
        return -1;
    }

    memcpy(p->key, key, p->key_size);
    memcpy(p->val, val, p->val_size);

    return 0;
}