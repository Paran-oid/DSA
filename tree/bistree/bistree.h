#ifndef BISTREE_H
#define BISTREE_H

#include "btree.h"

#define AVL_LFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct AvlNode_ {
    void* data;
    int hidden;
    int factor;
} AvlNode;

typedef BiTree AvlTree;

void bistree_create(AvlTree* tree, void (*destroy)(void* data), int (*match)(const void* key1, const void* key2));
void bistree_destroy(AvlTree* tree);

int bistree_insert(AvlTree* tree, const void* data);
int bistree_remove(AvlTree* tree, const void* data);
int bistree_lookup(AvlTree* tree, void** data);

#define bistree_size(tree) ((tree)->size)

#endif