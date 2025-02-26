#pragma once

#include "models.h"

#include <stdint.h>

uint32_t hash(HashTable *ht, char *item);
HashNode *hash_node_create(char *key, void *val, HashNode *next);

HashTable hash_table_create(DataType type1, DataType type2);
void hash_table_destroy(HashTable *ht);

void hash_table_insert(HashTable *ht, char *key, void *val);
void *hash_table_lookup(HashTable *ht, char *key);
void *hash_table_delete(HashTable *ht, char *key);
