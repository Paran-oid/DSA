#pragma once

#include "models.h"

TreeNode *treenode_create(void *val, TreeNode *left, TreeNode *right,
                          size_t element_size);

Tree *tree_create(DataType type);
void treenode_destroy(TreeNode *node);
void tree_destroy(Tree *tree);

TreeNode *tree_parent(TreeNode *tree, void *val, size_t element_size);
void tree_insert(Tree *tree, void *val);
void tree_delete(Tree *tree, void *val);
TreeNode *search_tree_node(TreeNode *node, void *val, size_t element_size);