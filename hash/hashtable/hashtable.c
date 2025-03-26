#include "hashtable.h"
#include "list.h"
#include "pair.h"

#include <stdlib.h>
#include <string.h>

void ht_create(HashTable* ht, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* key))
{
    if ((ht->table = malloc(sizeof(List) * buckets)) == NULL) {
        return;
    }
    ht->buckets = buckets;

    for (size_t i = 0; i < (size_t)buckets; i++) {
        list_create(&ht->table[i], match, destroy);
    }

    ht->destroy = destroy;
    ht->hash = hash;
    ht->match = match;

    ht->size = 0;
}
void ht_destroy(HashTable* ht)
{
    for (size_t i = 0; i < (size_t)ht->buckets; i++) {
        list_destroy(&ht->table[i]);
    }
    free(ht->table);
    memset(ht, 0, sizeof(HashTable));
}

int ht_insert(HashTable* ht, const void* data)
{
    void* temp;

    temp = (void*)data;
    if (ht_get(ht, &temp) == 0) {
        return 1;
    }
    int bucket = ht->hash(data) % ht->buckets;
    if ((list_ins_next(&ht->table[bucket], NULL, data)) == 0) {
        ht->size++;
        return 0;
    }
    return 0;
}

int ht_remove(HashTable* ht, void** data)
{
    int bucket;
    ListNode* curr;

    bucket = ht->hash(*data) % ht->buckets;

    for (curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
        if (ht->match(list_data(curr), *data)) {
            if ((list_rem_next(&ht->table[bucket], *data, NULL)) == 0) {
                ht->size--;
                return 0;
            } else {
                return 1;
            }
        }
    }

    return -1;
}

int ht_get(const HashTable* ht, void** data)
{
    ListNode* curr;
    int bucket = ht->hash(*data) % ht->buckets;

    for (curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
        if (ht->match(*data, list_data(curr))) {
            *data = list_data(curr);
            return 0;
        }
    }

    return -1;
}
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/******************************************Dictionary Behaivor********************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/

int ht_get_value(const HashTable* ht, const void* key, void** val)
{
    ListNode* curr;
    int bucket = ht->hash(key) % ht->buckets;

    for (curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
        void* found_key = ((Pair*)(curr->data))->key;
        if (ht->match(key, found_key)) {
            *val = ((Pair*)(curr->data))->val;
            return 0;
        }
    }

    return -1;
}

int ht_set(HashTable* ht, const Pair* pair)
{
    int res_val;
    Pair* data;
    void* temp;

    int bucket = ht->hash(pair->key) % ht->buckets;
    if (ht_get_value(ht, pair->key, &temp) == 0) {
        for (ListNode* curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
            void* found_key = ((Pair*)(curr->data))->key;
            if (ht->match(pair->key, found_key)) {
                ((Pair*)curr->data)->val = pair->val;
                return 0;
            }
        }
        return -1;
    }
    data = malloc(sizeof(Pair));
    data->key = malloc(pair->key_size);
    memcpy(data->key, pair->key, pair->key_size);

    data->val = malloc(pair->val_size);
    memcpy(data->val, pair->val, pair->val_size);

    if ((res_val = list_ins_next(&ht->table[bucket], NULL, data)) == 0) {
        ht->size++;
    } else {
        free(data->val);
        free(data->key);
        free(data);
    }
    return res_val;
}

int ht_remove_key(HashTable* ht, const void* key, void** data)
{
    int bucket;
    ListNode* curr;

    bucket = ht->hash(key) % ht->buckets;

    for (curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
        void* found_key = ((Pair*)(curr->data))->key;
        if (ht->match(found_key, key)) {
            if ((list_rem_next(&ht->table[bucket], NULL, data)) == 0) {
                ht->size--;
                return 0;
            } else {
                return 1;
            }
        }
    }

    return -1;
}