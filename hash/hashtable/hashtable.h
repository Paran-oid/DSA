#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list.h>
#include <stddef.h>

typedef struct HashTable_ {

    List* table;
    int buckets;

    size_t size;
    
    int (*hash)(const void* key);
    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* key);

} HashTable;

void ht_create(HashTable* ht, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* key));
void ht_destroy(HashTable* ht);

int ht_insert(HashTable* ht, const void* data);
int ht_remove(HashTable* ht, void** data);
int ht_get(const HashTable* ht, void** data);

#define ht_size(ht) ((ht)->size)

#endif