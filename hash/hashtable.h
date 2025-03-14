#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "core.h"
#include <list.h>
#include <stddef.h>

typedef struct HashTable_ {

    List* table;
    int buckets;

    size_t size;
    size_t item_size;

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

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/***************************************** Dictionary Behaivor *******************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/

int ht_get_value(const HashTable* ht, const void* key, void** value);
int ht_set(HashTable* ht, const Pair* pair);
int ht_remove_key(HashTable* ht, const void* key, void** data);

#endif