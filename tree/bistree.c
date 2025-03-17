#include "bistree.h"
#include "btree.h"

#include <stdlib.h>
#include <string.h>

static void left_destroy(BiTree* tree, BiTreeNode* node);
static void right_destroy(BiTree* tree, BiTreeNode* node);
static int insert(BiTree* tree, BiTreeNode** node, const void* data, int* balanced);
static int hide(BiTree* tree, BiTreeNode* node, const void* data);
static int lookup(BiTree* tree, BiTreeNode* node, void** data);

static void rotate_left(BiTreeNode** node)
{
    BiTreeNode* left = bitree_left(*node);
    if (((AvlNode*)bitree_data(*node))->factor == AVL_LFT_HEAVY) {
        // LL
        bitree_left(*node) = left->right;
        bitree_right(left) = *node;

        ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode*)bitree_data(left))->factor = AVL_BALANCED;

        *node = left;
    } else {
        // LR
        BiTreeNode* grandchild = bitree_right(left);
        bitree_left(*node) = bitree_right(grandchild);
        bitree_right(left) = bitree_left(grandchild);
        bitree_left(grandchild) = left;
        bitree_right(grandchild) = *node;

        switch (((AvlNode*)grandchild)->factor) {
        case AVL_BALANCED:
            ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode*)bitree_data(left))->factor = AVL_BALANCED;
            break;
        case AVL_LFT_HEAVY:
            ((AvlNode*)bitree_data(*node))->factor = AVL_RGT_HEAVY;
            ((AvlNode*)bitree_data(left))->factor = AVL_BALANCED;
            break;
        case AVL_RGT_HEAVY:
            ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode*)bitree_data(left))->factor = AVL_LFT_HEAVY;
            break;
        }

        ((AvlNode*)bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}
static void rotate_right(BiTreeNode** node)
{
    BiTreeNode* right = bitree_right(*node);
    if (((AvlNode*)bitree_data(right))->factor == AVL_RGT_HEAVY) {
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;

        ((AvlNode*)bitree_data(right))->factor = AVL_BALANCED;
        ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;

        *node = bitree_right(right);
    } else {
        BiTreeNode* grandchild = bitree_left(right);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;

        switch (((AvlNode*)bitree_data(grandchild))->factor) {
        case AVL_BALANCED:
            ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode*)bitree_data(right))->factor = AVL_BALANCED;
            break;
        case AVL_LFT_HEAVY:
            ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode*)bitree_data(right))->factor = AVL_RGT_HEAVY;
            break;
        case AVL_RGT_HEAVY:
            ((AvlNode*)bitree_data(*node))->factor = AVL_LFT_HEAVY;
            ((AvlNode*)bitree_data(right))->factor = AVL_BALANCED;
            break;
        }

        ((AvlNode*)bitree_data(right))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}

static void left_destroy(BiTree* tree, BiTreeNode* node)
{
    BiTreeNode** position;
    if (bitree_size(tree) == 0) {
        return;
    }

    if (node == NULL) {
        *position = bitree_root(tree);
    } else {
        *position = bitree_left(node);
    }

    if (*position != NULL) {
        left_destroy(tree, *position);
        right_destroy(tree, *position);
        if (tree->destroy != NULL) {
            tree->destroy(((AvlNode*)(*position)->data)->data);
        }
    }

    free((*position)->data);
    free(*position);
    *position = NULL;

    tree->size--;
}

static void right_destroy(BiTree* tree, BiTreeNode* node)
{
    BiTreeNode** position;
    if (bitree_size(tree) == 0) {
        return;
    }

    if (node == NULL) {
        *position = bitree_root(tree);
    } else {
        *position = node;
    }

    if (*position != NULL) {
        left_destroy(tree, *position);
        right_destroy(tree, *position);
    }

    if (*position != NULL) {
        left_destroy(tree, *position);
        right_destroy(tree, *position);
        if (tree->destroy != NULL) {
            tree->destroy(((AvlNode*)(*position)->data)->data);
        }
    }

    free((*position)->data);
    free(*position);
    *position = NULL;

    tree->size--;
}

static int insert(BiTree* tree, BiTreeNode* node, const void* data, int* balanced)
{
}
static int hide(BiTree* tree, BiTreeNode* node, const void* data)
{
}
static int lookup(BiTree* tree, BiTreeNode* node, void** data)
{
}

void bistree_create(AvlTree* tree, void (*destroy)(void* data), int (*match)(const void* key1, const void* key2))
{
    tree->destroy = destroy;
    tree->match = match;
    tree->root = NULL;
    tree->size = 0;
}
void bistree_destroy(AvlTree* tree)
{
    left_destroy(tree, NULL);
    memset(tree, 0, sizeof(AvlTree));
}

int bistree_insert(AvlTree* tree, const void* data)
{
    int balanced = 0;
    return insert(tree, &bitree_root(tree), data, &balanced);
}
int bistree_remove(AvlTree* tree, const void* data)
{
    return hide(tree, bitree_root(tree), data);
}
int bistree_lookup(AvlTree* tree, void** data)
{
    return lookup(tree, bitree_root(tree), data);
}