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

int ht_insert(HashTable* ht, void* key, void* val);
int ht_get();
int ht_remove();

#define ht_size(ht)((ht)->size)

#endif