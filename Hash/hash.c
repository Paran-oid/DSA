#include "hash.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t hash(HashTable *ht, char *item) {
  uint32_t hash_val = 0;
  for (size_t i = 0; i < strlen(item); i++) {
    hash_val += item[i];
    hash_val = (hash_val * item[i]) % ht->capacity;
  }
  return hash_val;
}

HashNode *hash_node_create(char *key, void *val, HashNode *next) {
  HashNode *node = malloc(sizeof(HashNode));
  node->key = key;
  node->val = val;
  node->next = next;

  return node;
}

HashTable hash_table_create(DataType type1, DataType type2) {
  HashTable ht;
  ht.element_size1 = type_map(type1);
  ht.element_size2 = type_map(type2);

  ht.type1 = type1;
  ht.type2 = type2;

  ht.capacity = 100;
  ht.size = 0;

  ht.buckets = malloc(sizeof(HashNode) * ht.capacity);
  return ht;
}

void hash_table_destroy(HashTable *ht) {
  for (size_t i = 0; i < ht->capacity; i++) {
    HashNode *curr = ht->buckets[i];
    while (curr != NULL) {
      HashNode *temp = curr;
      curr = curr->next;
      free(temp->key);
      free(temp->val);
      free(temp);
    }
  }
  free(ht->buckets);
}

void hash_table_insert(HashTable *ht, char *key, void *val) {
  HashNode *item = hash_table_lookup(ht, key);
  uint32_t hash_val = hash(ht, key);

  if (item == NULL) {
    item = hash_node_create(key, val, NULL);
    ht->buckets[hash_val] = item;
  } else {
    HashNode *curr = item;
    while (curr->next != NULL)
      curr = curr->next;
    curr->next = item;
  }
}
void *hash_table_lookup(HashTable *ht, char *key) {
  uint32_t hash_val = hash(ht, key);
  if (ht->buckets[hash_val] != NULL) {
    HashNode *curr = ht->buckets[hash_val];
    while (strcmp(curr->key, key) != 0 && curr != NULL)
      curr = curr->next;
    return curr;
  }
  return NULL;
}
void *hash_table_delete(HashTable *ht, char *key) {
  uint32_t hash_val = hash(ht, key);
  HashNode *curr = ht->buckets[hash_val], *prev = NULL;

  while (curr != NULL) {
    if (strcmp(key, curr->key) == 0) {
      prev = curr->next;
      curr->next = NULL;
      return curr->val;
    }
    prev = curr;
    curr = curr->next;
  }

  return NULL;
}
