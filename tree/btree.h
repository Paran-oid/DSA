#ifndef BTREE_H
#define BTREE_H

#include <stddef.h>

typedef struct BiTreeNode_ {
    void* data;
    struct BiTreeNode_* left;
    struct BiTreeNode_* right;
} BiTreeNode;

typedef struct BiTree_ {
    BiTreeNode* root;
    size_t size;

    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* key);
} BiTree;

void bitree_create(BiTree* bt, void (*destroy)(void* key), int (*match)(const void* key1, const void* key2));
void bitree_destroy(BiTree* bt);

int bitree_ins_left(BiTree* bt, BiTreeNode* node, const void* data);
int bitree_ins_right(BiTree* bt, BiTreeNode* node, const void* data);

int bitree_rem_left(BiTree* bt, BiTreeNode* node);
int bitree_rem_right(BiTree* bt, BiTreeNode* node);

int bitree_merge(BiTree* bt_left, BiTree* bt_right, BiTree* bt_res, const void* data);

#define bitree_size(bt) ((bt)->size)
#define bitree_root(bt) ((bt)->root)
#define bitree_is_root(bt, node) ((bt)->root == node)
#define bitree_is_eob(node) ((node) == NULL)
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)
#define bitree_data(node) ((node)->data)

#endif