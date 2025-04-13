#ifndef OBJPOOL_H
#define OBJPOOL_H

#include <stdbool.h>
#include <stddef.h>

typedef struct PoolObj_ {
    bool allocated;
    void* obj;
    size_t elsize;
} PoolObj;

typedef struct Pool_ {
    PoolObj* objects;
    size_t size;
} Pool;

void pool_create(Pool* pool, size_t size, size_t elsize);
void pool_destroy(Pool* pool);

int pool_borrow(Pool* pool, void** data);
int pool_return(Pool* pool, void* data);

#endif