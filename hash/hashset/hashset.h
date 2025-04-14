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

} HashSet;

void ht_create(HashSet* ht, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* key));
void ht_destroy(HashSet* ht);

int ht_insert(HashSet* ht, const void* data);
int ht_remove(HashSet* ht, void** data);
int ht_get(const HashSet* ht, void* val, void** data);

#define ht_size(ht) ((ht)->size)

#endif
