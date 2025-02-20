#include "tree.h"
#include "funcs.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

treenode_t *treenode_create(void *val, treenode_t *left, treenode_t *right,
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

tree_t *tree_create(enum datatype type) {
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

treenode_t *tree_parent(treenode_t *root, void *val, usize tsize) {
  if (!root)
    return NULL;

  if ((root->left && memcmp(root->left->val, val, tsize) == 0) ||
      (root->right && memcmp(root->right->val, val, tsize) == 0)) {
    return root;
  }

  treenode_t *right_parent = tree_parent(root->right, val, tsize);
  if (right_parent) {
    return right_parent;
  }

  return tree_parent(root->left, val, tsize);

  return NULL;
}
void tree_insert(tree_t *tree, void *val) {
  ASSERT(val, "Null item passed to tree_insert\n");

  treenode_t *node = treenode_create(val, NULL, NULL, tree->tsize);

  if (tree->root == NULL) {
    tree->root = node;
    return;
  }

  queue_t *q = queue_create(TREENODE);
  enqueue(q, &(tree->root));
  while (q->front) {
    treenode_t *current = *(treenode_t **)dequeue(q);
    if (current->val == node->val) {
      break;
    }

    if (current->left == NULL) {
      current->left = node;
      break;
    }
    enqueue(q, &(current->left));

    if (current->right == NULL) {
      current->right = node;
      break;
    }
    enqueue(q, &(current->right));
  }

  queue_destroy(q);
}

static void tree_helper_delete(treenode_t *root, treenode_t **lastptr,
                               treenode_t **itemptr, void *val, usize tsize) {
  if (!root)
    return;

  if (memcmp(root->val, val, tsize) == 0)
    *itemptr = root;

  tree_helper_delete(root->left, lastptr, itemptr, val, tsize);
  *lastptr = root;
  tree_helper_delete(root->right, lastptr, itemptr, val, tsize);
}

void tree_delete(tree_t *tree, void *val) {
  treenode_t *lastptr = NULL, *itemptr = NULL, *parentptr = NULL;

  tree_helper_delete(tree->root, &lastptr, &itemptr, val, tree->tsize);

  if (itemptr && lastptr)
    memcpy(itemptr->val, lastptr->val, tree->tsize);

  parentptr = tree_parent(tree->root, lastptr->val, tree->tsize);

  if (parentptr->right)
    parentptr->right = NULL;
  else
    parentptr->left = NULL;

  free(lastptr);
}
treenode_t *search_tree_node(treenode_t *node, void *val, usize tsize) {
  if (node == NULL)
    return NULL;

  treenode_t *left_node = search_tree_node(node->left, val, tsize);
  if (left_node)
    return left_node;

  if (memcmp(node->val, val, tsize) == 0) {
    return node;
  }

  return search_tree_node(node->right, val, tsize);
}