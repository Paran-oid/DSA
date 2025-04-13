#include "objpool.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void pool_create(Pool* pool, size_t size, size_t elsize)
{
    pool->objects = calloc(size, sizeof(PoolObj));
    pool->size = size;
    for (size_t i = 0; i < size; i++) {
        pool->objects[i].elsize = elsize;
        pool->objects[i].obj = malloc(elsize);
    }
}
void pool_destroy(Pool* pool)
{
    for (size_t i = 0; i < pool->size; i++) {
        free(pool->objects[i].obj);
    }
    free(pool->objects);
    memset(pool, 0, sizeof(Pool));
}

int pool_borrow(Pool* pool, void** data)
{
    for (size_t i = 0; i < pool->size; i++) {
        if (!pool->objects[i].allocated) {
            pool->objects[i].allocated = true;
            *data = pool->objects[i].obj;
            return 0;
        }
    }
    return 1;
}
int pool_return(Pool* pool, void* data)
{
    for (size_t i = 0; i < pool->size; i++) {
        if (pool->objects[i].obj == data) {
            pool->objects[i].allocated = false;
            return 0;
        }
    }
    return 1;
}
