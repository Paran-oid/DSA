#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHAR 256

typedef struct TrieNode_ {
    struct TrieNode_* children[NUM_CHAR];
    bool terminal;
} TrieNode;

TrieNode* node_create(void)
{
    TrieNode* node = malloc(sizeof(TrieNode));
    for (size_t i = 0; i < NUM_CHAR; i++) {
        node->children[i] = NULL;
    }
    node->terminal = false;
    return node;
}

void trie_destroy(TrieNode* node)
{
    for (size_t i = 0; i < NUM_CHAR; i++) {
        if (node->children[i]) {
            trie_destroy(node->children[i]);
        }
    }
    free(node);
}

int trie_insert(TrieNode** root, char* signedtext)
{
    if (*root == NULL) {
        *root = node_create();
    }

    unsigned char* text = (unsigned char*)signedtext;
    TrieNode* node = *root;
    size_t length = strlen(signedtext);

    for (size_t i = 0; i < length; i++) {
        if (node->children[text[i]] == NULL) {
            node->children[text[i]] = node_create();
        }
        node = node->children[text[i]];
    }

    if (node->terminal) {
        return 0;
    } else {
        node->terminal = true;
        return 1;
    }
}

int trie_search(TrieNode* root, char* signedtext)
{
    unsigned char* text = (unsigned char*)signedtext;
    size_t length = strlen(signedtext);
    TrieNode* curr = root;

    for (size_t i = 0; i < length; i++) {
        if (curr->children[text[i]] == NULL) {
            return 0;
        }
        curr = curr->children[text[i]];
    }

    return curr->terminal;
}

bool node_has_children(TrieNode* node)
{
    if (node == NULL)
        return false;

    for (size_t i = 0; i < NUM_CHAR; i++) {
        if (node->children[i]) {
            return true;
        }
    }
    return false;
}

TrieNode* trie_delete_helper(TrieNode* node, unsigned char* text, bool* deleted)
{
    if (node == NULL)
        return node;

    if (*text == '\0') {
        if (node->terminal) {
            node->terminal = false;
            *deleted = false;

            if (!node_has_children(node)) {
                free(node);
                node = NULL;
            }
        }
        return node;
    }
    node->children[text[0]] = trie_delete_helper(node->children[text[0]], text + 1, deleted);
    if (*deleted && !node_has_children(node) && node->terminal) {
        free(node);
        node = NULL;
    }

    return node;
}

int trie_delete(TrieNode** root, char* signedtext)
{
    unsigned char* text = (unsigned char*)signedtext;
    bool result = false;

    if (*root == NULL)
        return false;

    *root = trie_delete_helper(*root, text, &result);
    return result;
}

void trie_print_helper(TrieNode* node, unsigned char* prefix, int length)
{
    unsigned char newprefix[length + 2];
    memcpy(newprefix, prefix, length);
    newprefix[length + 1] = '\0';

    if (node->terminal) {
        printf("WORD: %s\n", prefix);
    }

    for (size_t i = 0; i < NUM_CHAR; i++) {
        if (node->children[i] != NULL) {
            newprefix[length] = i;
            trie_print_helper(node->children[i], newprefix, length + 1);
        }
    }
}

void trie_print(TrieNode* root)
{
    if (root == NULL) {
        printf("TRIE EMPTY;\n");
        return;
    }
    trie_print_helper(root, NULL, 0);
}
