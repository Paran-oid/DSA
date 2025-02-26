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

HashNode *hash_node_create(HashTable *ht, void *key, void *val,
                           HashNode *next) {
  HashNode *node = malloc(sizeof(HashNode));

  if (!node) {
    perror("couldn't allocate memory for hash node\n");
    exit(EXIT_FAILURE);
  }

  node->key = malloc(ht->element_size1);
  if (!node->key) {
    perror("couldn't initialize hashtable node key;\n");
    exit(EXIT_FAILURE);
  }

  memcpy(node->key, key, ht->element_size1);

  node->val = malloc(ht->element_size2);
  if (!node->val) {
    perror("couldn't initialize hashtable node value;\n");
    exit(EXIT_FAILURE);
  }

  memcpy(node->val, val, ht->element_size2);

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

  ht.buckets = (HashNode **)malloc(sizeof(HashNode *));
  if (!ht.buckets) {
    perror("couldn't initialize hashtable buckets\n");
    exit(EXIT_FAILURE);
  }

  return ht;
}

void hash_table_destroy(HashTable *ht) {
  if (!ht)
    return;

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
  uint32_t hash_val = hash(ht, key);
  HashNode *current = ht->buckets[hash_val];

  while (current) {
    if (memcmp(current->key, key, ht->element_size1) == 0) {
      free(current->val);
      current->val = malloc(ht->element_size2);
      memcpy(current->val, val, ht->element_size2);
      return;
    }
    current = current->next;
  }

  HashNode *new_node = hash_node_create(ht, key, val, NULL);
  new_node->next = ht->buckets[hash_val];
  ht->buckets[hash_val] = new_node;

  ht->size++;
}
void *hash_table_lookup(HashTable *ht, char *key) {
  uint32_t hash_val = hash(ht, key);
  if (ht->buckets[hash_val] != NULL) {
    HashNode *curr = ht->buckets[hash_val];
    while (curr != NULL)
      curr = curr->next;

    if (curr == NULL)
      return curr;

    while (curr->next != NULL) {
      if (strcmp(curr->key, key) == 0) {
        return curr->val;
      }
      curr = curr->next;
    }

    return NULL;
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

    ht->size--;
  }

  return NULL;
}
