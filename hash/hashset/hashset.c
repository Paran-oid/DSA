#include "hashset.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>

void ht_create(HashSet* ht, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* key))
{
    if ((ht->table = calloc(sizeof(List), (size_t)buckets)) == NULL) {
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
void ht_destroy(HashSet* ht)
{
    for (size_t i = 0; i < (size_t)ht->buckets; i++) {
        list_destroy(&ht->table[i]);
    }
    free(ht->table);
    memset(ht, 0, sizeof(HashSet));
}

int ht_insert(HashSet* ht, const void* data)
{
    void* temp;

    temp = (void*)data;
    if (ht_get(ht, temp, NULL) == 0) {
        return 1;
    }
    int bucket = ht->hash(data) % ht->buckets;
    if ((list_ins_next(&ht->table[bucket], NULL, data)) == 0) {
        ht->size++;
        return 0;
    }
    return 0;
}

int ht_remove(HashSet* ht, void** data)
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

int ht_get(const HashSet* ht, void* val, void** data)
{
    ListNode* curr;
    int bucket = ht->hash(val) % ht->buckets;

    for (curr = list_head(&ht->table[bucket]); curr != NULL; curr = list_next(curr)) {
        if (ht->match(val, list_data(curr))) {
            *data = list_data(curr);
            return 0;
        }
    }

    return -1;
}
