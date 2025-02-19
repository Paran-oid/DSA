#pragma once

#include "funcs.h"

typedef struct treenode {
  void *val;
  struct treenode *right;
  struct treenode *left;
  usize tsize;
} treenode_t;

typedef struct tree {
  treenode_t *root;
  usize tsize;
} tree_t;

typedef enum traverse_mode { INORD, PRE, POST, LEVEL } traverse_mode_t;

treenode_t *tree_node_init(void *val, treenode_t *left, treenode_t *right);

tree_t *tree_init(enum datatype type);
void tree_destroy(tree_t *t);

// void tree_insert(tree_t *tree, void *val);
// void tree_delete(tree_t *tree, void *val);
// treenode_t *tree_search(const tree_t *tree, void *val);
