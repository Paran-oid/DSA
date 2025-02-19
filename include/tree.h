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
  enum datatype type;
} tree_t;

typedef enum traverse_mode { INORD, PRE, POST, LEVEL } traverse_mode_t;

treenode_t *treenode_init(void *val, treenode_t *left, treenode_t *right,
                          usize tsize);

tree_t *tree_init(enum datatype type);
void treenode_destroy(treenode_t *node);
void tree_destroy(tree_t *tree);

void tree_insert(tree_t *tree, void *val);
// void tree_delete(tree_t *tree, void *val);
// treenode_t *tree_search(const tree_t *tree, void *val);
