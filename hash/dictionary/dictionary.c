#include "dictionary.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>

static int hash_djb2(const void* data)
{
    const char* str = (const char*)data;
    int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static int cmp(const void* key1, const void* key2)
{
    return strcmp((const char*)key1, (const char*)key2) == 0 ? 1 : 0;
}

void dict_create(Dictionary* dict, void (*destroy)(void*))
{
    dict->buckets = BUCKETS;
    dict->destroy = destroy;
    dict->hash = hash_djb2;
    dict->match = cmp;
    dict->size = 0;

    if ((dict->table = calloc(sizeof(List), BUCKETS)) == NULL) {
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < BUCKETS; i++) {
        list_create(&dict->table[i], dict->match, destroy);
    }
}
void dict_destroy(Dictionary* dict)
{
    list_destroy(dict->table);
}

int dict_get_value(const HashTable* dict, const char* key, char** val)
{
    ListNode* curr;
    int bucket = dict->hash(key) % dict->buckets;

    for (curr = list_head(&dict->table[bucket]); curr != NULL; curr = list_next(curr)) {
        char* found_key = ((Pair*)(curr->data))->key;
        if (dict->match(key, found_key)) {
            *val = ((Pair*)(curr->data))->val;
            return 0;
        }
    }

    return -1;
}

int dict_set(HashTable* dict, const char* key, const char* val)
{
    int res_val;
    Pair* data;
    char* temp;

    int bucket = dict->hash(key) % dict->buckets;
    if (dict_get_value(dict, key, &temp) == 0) {
        for (ListNode* curr = list_head(&dict->table[bucket]); curr != NULL; curr = list_next(curr)) {
            void* found_key = ((Pair*)(curr->data))->key;
            if (dict->match(key, found_key)) {
                ((Pair*)curr->data)->val = val;
                return 0;
            }
        }
        return -1;
    }

    data = malloc(sizeof(Pair));
    char* key_cpy = calloc(sizeof(char), strlen(key) + 1);
    char* val_cpy = calloc(sizeof(char), strlen(val) + 1);

    memcpy(key_cpy, key, strlen(key) + 1);
    memcpy(val_cpy, val, strlen(val) + 1);

    data->key = (void*)key_cpy;
    data->val = (void*)val_cpy;

    if ((res_val = list_ins_next(&dict->table[bucket], NULL, data)) == 0) {
        dict->size++;
    } else {
        free(val_cpy);
        free(key_cpy);
    }
    return res_val;
}

int dict_remove_key(HashTable* dict, const char* key, char** data)
{
    int bucket;
    ListNode* curr;

    bucket = dict->hash(key) % dict->buckets;

    for (curr = list_head(&dict->table[bucket]); curr != NULL; curr = list_next(curr)) {
        void* found_key = ((Pair*)(curr->data))->key;
        if (dict->match(found_key, key)) {
            if ((list_rem_next(&dict->table[bucket], NULL, (void**)data)) == 0) {
                *data = ((Pair*)*data)->val;
                dict->size--;
                return 0;
            } else {
                return 1;
            }
        }
    }

    return -1;
}