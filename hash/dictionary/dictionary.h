#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "hashset.h"

#define BUCKETS 100

typedef HashSet Dictionary;

typedef struct Pair_ {
    void* key;
    void* val;
} Pair;

void dict_create(Dictionary* dict, void (*destroy)(void* key));
void dict_destroy(Dictionary* dict);

int dict_get_value(const HashSet* ht, const char* key, char** data);
int dict_set(HashSet* ht, const char* key, const char* val);
int dict_remove_key(HashSet* ht, const char* key, void** data);

#endif
