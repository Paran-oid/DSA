#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list.h>
#include <stddef.h>

typedef struct HashTable_ {

    List* buckets;

    size_t size;
    size_t item_size;

    int (*hash)(const void* key);
    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* key);

} HashTable;

void ht_init(HashTable* ht, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* key));
void ht_destroy(HashTable* ht);

int ht_insert(HashTable* ht, void* data);
int ht_remove(HashTable* ht, void** data);
int ht_get(HashTable* ht, void** data);

#define ht_size(ht) ((ht)->size)

#endif