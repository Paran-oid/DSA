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

treenode_t *treenode_create(void *val, treenode_t *left, treenode_t *right,
                            usize tsize);

tree_t *tree_create(enum datatype type);
void treenode_destroy(treenode_t *node);
void tree_destroy(tree_t *tree);

treenode_t *tree_parent(treenode_t *tree, void *val, usize tsize);
void tree_insert(tree_t *tree, void *val);
void tree_delete(tree_t *tree, void *val);
treenode_t *search_tree_node(treenode_t *node, void *val, usize tsize);