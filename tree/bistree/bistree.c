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
        position = &bitree_root(tree);
    } else {
        position = &bitree_left(node);
    }

    if (*position != NULL) {
        left_destroy(tree, *position);
        right_destroy(tree, *position);
        if (tree->destroy != NULL) {
            tree->destroy(((AvlNode*)(*position)->data)->data);
        }
    }

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
        position = &bitree_root(tree);
    } else {
        position = &bitree_right(node);
    }

    if (*position != NULL) {
        left_destroy(tree, *position);
        right_destroy(tree, *position);
        if (tree->destroy != NULL) {
            tree->destroy(((AvlNode*)(*position)->data)->data);
        }
    }

    free(*position);
    *position = NULL;

    tree->size--;
}

static int insert(BiTree* tree, BiTreeNode** node, const void* data, int* balanced)
{
    AvlNode* avl_data;
    int cmp_val, ret_val;

    if (bitree_is_eob(*node)) {
        if ((avl_data = (AvlNode*)malloc(sizeof(AvlNode))) == NULL) {
            return -1;
        }
        avl_data->factor = AVL_BALANCED;
        avl_data->data = (void*)data;
        avl_data->hidden = 0;

        if ((ret_val = bitree_ins_left(tree, *node, avl_data)) != 0) {
            return -1;
        }
        *balanced = 0;
    } else {
        cmp_val = tree->match(data, ((AvlNode*)bitree_data(*node))->data);
        if (cmp_val < 0) {
            if (bitree_is_eob(bitree_left(*node))) {
                if ((avl_data = (AvlNode*)malloc(sizeof(AvlNode))) == NULL) {
                    return -1;
                }
                avl_data->data = (void*)data;
                avl_data->hidden = 0;
                avl_data->factor = AVL_BALANCED;

                if (bitree_ins_left(tree, *node, avl_data) == -1) {
                    return -1;
                }
                *balanced = 0;
            } else {
                if ((ret_val = insert(tree, &bitree_left(*node), data, balanced)) != 0) {
                    return ret_val;
                }
            }

            if (!(*balanced)) {
                switch (((AvlNode*)bitree_data(*node))->factor) {
                case AVL_LFT_HEAVY:
                    rotate_left(node);
                    *balanced = 1;
                    break;
                case AVL_BALANCED:
                    ((AvlNode*)bitree_data(*node))->factor = AVL_LFT_HEAVY;
                    break;
                case AVL_RGT_HEAVY:
                    ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
                    *balanced = 1;
                    break;
                }
            }
        } else if (cmp_val > 0) {
            if (bitree_is_eob(bitree_right(*node))) {
                if ((avl_data = (AvlNode*)malloc(sizeof(AvlNode))) == NULL) {
                    return -1;
                }
                avl_data->data = (void*)data;
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;

                if (bitree_ins_right(tree, *node, avl_data) != 0) {
                    return -1;
                }

                *balanced = 0;
            } else {
                if ((ret_val = insert(tree, &bitree_right(*node), data, balanced)) != 0) {
                    return ret_val;
                }
            }

            if (!(*balanced)) {
                switch (((AvlNode*)bitree_data(*node))->factor) {
                case AVL_RGT_HEAVY:
                    rotate_right(node);
                    *balanced = 1;
                    break;
                case AVL_BALANCED:
                    ((AvlNode*)bitree_data(*node))->factor = AVL_RGT_HEAVY;
                    break;
                case AVL_LFT_HEAVY:
                    ((AvlNode*)bitree_data(*node))->factor = AVL_BALANCED;
                    break;
                }
            }
        } else {
            if (!((AvlNode*)bitree_data(*node))->hidden) {
                return 1;
            } else {
                if (tree->destroy) {
                    tree->destroy(((AvlNode*)bitree_data(*node))->data);
                }

                ((AvlNode*)bitree_data(*node))->data = (void*)data;
                ((AvlNode*)bitree_data(*node))->hidden = 0;

                *balanced = 1;
            }
        }
    }
    return 0;
}
static int hide(BiTree* tree, BiTreeNode* node, const void* data)
{
    int cmp_val, ret_val;

    if (bitree_is_eob(node)) {
        return -1;
    }

    cmp_val = tree->match(data, ((AvlNode*)bitree_data(node))->data);

    if (cmp_val < 0) {
        ret_val = hide(tree, bitree_left(node), data);
    } else if (cmp_val > 0) {
        ret_val = hide(tree, bitree_right(node), data);
    } else {
        ((AvlNode*)bitree_data(node))->hidden = 1;
        ret_val = 0;
    }

    return ret_val;
}
static int lookup(BiTree* tree, BiTreeNode* node, void** data)
{
    int ret_val, cmp_val;

    if (bitree_is_eob(node)) {
        return -1;
    }

    cmp_val = tree->match(*data, ((AvlNode*)bitree_data(node))->data);

    if (cmp_val < 0) {
        ret_val = lookup(tree, bitree_left(node), data);
    } else if (cmp_val > 0)
        ret_val = lookup(tree, bitree_right(node), data);
    else {
        if (!((AvlNode*)bitree_data(node))->hidden) {
            *data = ((AvlNode*)bitree_data(node))->data;
            return 0;
        } else {
            return -1;
        }
    }

    return ret_val;
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