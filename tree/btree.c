#include "btree.h"

#include <stdlib.h>
#include <string.h>

void bitree_create(BiTree* bt, void (*destroy)(void* key), int (*match)(const void* key1, const void* key2))
{
    bt->root = NULL;
    bt->size = 0;
    bt->destroy = destroy;
    bt->match = match;
}
void bitree_destroy(BiTree* bt)
{
    bitree_rem_left(bt, NULL);
    memset(bt, 0, sizeof(BiTree));
}
int bitree_ins_left(BiTree* bt, BiTreeNode* node, const void* data)
{
    BiTreeNode** pos;
    if (node == NULL) {
        if (bt->size > 0) {
            return -1;
        }
        pos = &bt->root;
    } else {
        if (bitree_left(node) != NULL) {
            return -1;
        }
        pos = &node->left;
    }

    BiTreeNode* new_node = malloc(sizeof(BiTreeNode));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = (void*)data;
    new_node->left = new_node->right = NULL;
    *pos = new_node;

    bt->size++;

    return 0;
}
int bitree_ins_right(BiTree* bt, BiTreeNode* node, const void* data)
{
    BiTreeNode** pos;
    if (node == NULL) {
        if (bt->size > 0) {
            return -1;
        }
        pos = &bt->root;
    } else {
        if (bitree_right(node) != NULL) {
            return -1;
        }
        pos = &node->right;
    }

    BiTreeNode* new_node = malloc(sizeof(BiTreeNode));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = (void*)data;
    new_node->left = new_node->right = NULL;
    *pos = new_node;

    bt->size++;

    return 0;
}

int bitree_rem_left(BiTree* bt, BiTreeNode* node)
{
    BiTreeNode** pos;

    if (bt->root == NULL) {
        return 1;
    }

    if (node == NULL) {
        pos = &bt->root;
    } else {
        pos = &node->left;
    }

    if (*pos != NULL) {
        bitree_rem_left(bt, *pos);
        bitree_rem_right(bt, *pos);
        if (bt->destroy) {
            bt->destroy((*pos)->data);
        }
    }

    bt->destroy(*pos);

    *pos = NULL;
    bt->size--;
    return 0;
}
int bitree_rem_right(BiTree* bt, BiTreeNode* node)
{
    BiTreeNode** pos;
    if (bitree_size(bt) == 0) {
        return 1;
    }

    if (node == NULL) {
        pos = &bt->root;
    } else {
        pos = &node->right;
    }

    if (*pos != NULL) {
        bitree_rem_left(bt, *pos);
        bitree_rem_right(bt, *pos);

        if (bt->destroy) {
            bt->destroy((*pos)->data);
        }
    }
    bt->destroy(*pos);
    *pos = NULL;

    bt->size--;
    return 0;
}

int bitree_merge(BiTree* bt_left, BiTree* bt_right, BiTree* bt_res, const void* data)
{
    if (!bt_left && !bt_right) {
        return 1;
    }

    bitree_create(bt_res, bt_left->destroy, bt_left->match);
    if (bitree_ins_left(bt_res, NULL, data) != 0) {
        bitree_destroy(bt_res);
        return -1;
    }

    bitree_root(bt_res)->left = bitree_root(bt_left);
    bitree_root(bt_res)->right = bitree_root(bt_right);

    bt_res->size = bitree_size(bt_left) + bitree_size(bt_right) + 1;

    bt_left->root = NULL;
    bt_left->size = 0;

    bt_right->root = NULL;
    bt_right->size = 0;

    return 0;
}