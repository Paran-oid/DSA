#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hashtable.h"

#define BUCKETS 100

typedef HashTable Dictionary;

typedef struct Pair_ {
    void* key;
    void* val;
} Pair;

void dict_create(Dictionary* dict, void (*destroy)(void* key));
void dict_destroy(Dictionary* dict);

int dict_get_value(const HashTable* ht, const char* key, char** data);
int dict_set(HashTable* ht, const char* key, const char* val);
int dict_remove_key(HashTable* ht, const char* key, char** data);

#endif