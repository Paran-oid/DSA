#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct TrieNode_ TrieNode;

TrieNode* node_create(void);

int trie_insert(TrieNode** root, char* word);
int trie_search(TrieNode* root, char* word);
int trie_delete(TrieNode** root, char* word);
void trie_print(TrieNode* root);
void trie_destroy(TrieNode* root);

#endif

