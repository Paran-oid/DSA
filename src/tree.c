#include "tree.h"
#include "funcs.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

treenode_t *treenode_init(void *val, treenode_t *left, treenode_t *right,
                          usize tsize) {
  treenode_t *mynode = malloc(sizeof(treenode_t));

  if (!mynode) {
    perror("There was an error allocating memory for treenode\n");
    exit(EXIT_FAILURE);
  }

  mynode->left = left;
  mynode->right = right;
  mynode->val = malloc(tsize);

  if (!mynode->val) {
    perror("There was an error allocating memory for treenode val\n");
    free(mynode);
    exit(EXIT_FAILURE);
  }

  memcpy(mynode->val, val, tsize);

  return mynode;
}

tree_t *tree_init(enum datatype type) {
  tree_t *tree = malloc(sizeof(tree_t));
  tree->root = NULL;
  tree->tsize = type_map(type);
  tree->type = type;

  return tree;
}

void treenode_destroy(treenode_t *node) {
  if (node == NULL)
    return;

  treenode_destroy(node->left);
  treenode_destroy(node->right);
  free(node);
}
void tree_destroy(tree_t *tree) {
  if (!tree)
    return;

  treenode_destroy(tree->root);
  free(tree);
}

// FIXME

void tree_insert(tree_t *tree, void *val) {
  ASSERT(val, "Null item passed to tree_insert\n");

  treenode_t *node = treenode_init(val, NULL, NULL, tree->tsize);
  printf("address of root is %p\n", tree->root);

  if (!tree->root) {
    tree->root = node;
    return;
  }

  queue_t *q = queue_init(TREENODE);
  enqueue(q, tree->root);
  while (q->front) {
    treenode_t *current = (treenode_t *)dequeue(q);
    printf("address of current is %d\n", current->val);

    // if (!current->left) {
    //   current->left = node;
    //   break;
    // }
    // enqueue(q, current->left);

    // if (!current->right) {
    //   current->right = node;
    //   break;
    // }
    // enqueue(q, current->right);
  }

  queue_destroy(q);
}

// void delete_tree_node(TreeNode **node) {}
// TreeNode *search_tree_node(TreeNode *node, i32 val) {
//   if (node == NULL)
//     return;

//   if (node->val == val) {
//     return node;
//   }

//   TreeNode *leftRes = search_tree_node(node->left, val);
//   return search_tree_node(node->right, val) ? leftRes == NULL : leftRes;
// }