#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash function for integers
int hash_int(const void* key)
{
    return (*(int*)key) % 10;
}

// Match function for integers
int match_int(const void* key1, const void* key2)
{
    return (*(int*)key1 == *(int*)key2);
}

// Destroy function (not needed for integers)
void destroy_int(void* key)
{
    free(key);
}

int main()
{
    HashTable ht;
    ht_create(&ht, 10, hash_int, match_int, destroy_int);

    // Insert key-value pairs
    Pair pair1 = { .key = malloc(sizeof(int)), .value = malloc(sizeof(int)), .key_size = sizeof(int), .value_size = sizeof(int) };
    *(int*)pair1.key = 5;
    *(int*)pair1.value = 100;
    ht_set(&ht, &pair1);

    Pair pair2 = { .key = malloc(sizeof(int)), .value = malloc(sizeof(int)), .key_size = sizeof(int), .value_size = sizeof(int) };
    *(int*)pair2.key = 15;
    *(int*)pair2.value = 200;
    ht_set(&ht, &pair2);

    // Retrieve values
    void* value;
    if (ht_get_value(&ht, pair1.key, &value) == 0) {
        printf("Key 5 -> Value: %d\n", *(int*)value);
    } else {
        printf("Key 5 not found!\n");
    }

    if (ht_get_value(&ht, pair2.key, &value) == 0) {
        printf("Key 15 -> Value: %d\n", *(int*)value);
    } else {
        printf("Key 15 not found!\n");
    }

    // Update value
    *(int*)pair1.value = 999;
    ht_set(&ht, &pair1);
    if (ht_get_value(&ht, &pair1.key, &value) == 0) {
        printf("Updated Key 5 -> Value: %d\n", *(int*)value);
    }

    // Remove key-value pair
    void* removed_data;
    if (ht_remove_key(&ht, &pair1.key, &removed_data) == 0) {
        printf("Removed Key 5 -> Value: %d\n", *(int*)((Pair*)removed_data)->value);
        free(((Pair*)removed_data)->key);
        free(((Pair*)removed_data)->value);
        free(removed_data);
    }

    if (ht_get_value(&ht, &pair1.key, &value) == -1) {
        printf("Key 5 successfully removed.\n");
    }

    // Cleanup
    ht_destroy(&ht);

    return 0;
}
