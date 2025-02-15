#pragma once
#include "funcs.h"

typedef struct TreeNode {
  i32 val;
  struct TreeNode *right;
  struct TreeNode *left;
} TreeNode;

typedef enum TraverseMode { INORD, PRE, POST, LEVEL } TraverseMode;

TreeNode *init_tree_node(i32 val);
void print_tree(TreeNode *node, TraverseMode mode);
void destroy_tree_node(TreeNode *node);

// TODO

// void insert_tree_node(TreeNode *node, i32 val);
// void delete_tree_node(TreeNode **node);
// TreeNode *search_tree_node(TreeNode *node, i32 val);