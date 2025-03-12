#include "core.h"
#include <string.h>

void swap(void* key1, void* key2, size_t item_size)
{
    void* temp = malloc(item_size);
    memcpy(temp, key1, item_size);
    memcpy(key1, key2, item_size);
    memcpy(key2, temp, item_size);
    free(temp);
}