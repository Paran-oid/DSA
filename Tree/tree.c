#include "tree.h"
#include "funcs.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode *treenode_create(void *val, TreeNode *left, TreeNode *right,
                          size_t element_size) {
  TreeNode *mynode = malloc(sizeof(TreeNode));

  if (!mynode) {
    perror("There was an error allocating memory for treenode\n");
    exit(EXIT_FAILURE);
  }

  mynode->left = left;
  mynode->right = right;
  mynode->value = malloc(element_size);

  if (!mynode->value) {
    perror("There was an error allocating memory for treenode val\n");
    free(mynode);
    exit(EXIT_FAILURE);
  }

  memcpy(mynode->value, val, element_size);

  return mynode;
}

Tree *tree_create(DataType type) {
  Tree *tree = malloc(sizeof(Tree));
  tree->root = NULL;
  tree->element_size = type_map(type);
  tree->type = type;

  return tree;
}

void treenode_destroy(TreeNode *node) {
  if (node == NULL)
    return;

  treenode_destroy(node->left);
  treenode_destroy(node->right);
  free(node->value); // Don't forget to free the value memory
  free(node);
}

void tree_destroy(Tree *tree) {
  if (!tree)
    return;

  treenode_destroy(tree->root);
  free(tree);
}

TreeNode *tree_parent(TreeNode *root, void *val, size_t element_size) {
  if (!root)
    return NULL;

  if ((root->left && memcmp(root->left->value, val, element_size) == 0) ||
      (root->right && memcmp(root->right->value, val, element_size) == 0)) {
    return root;
  }

  TreeNode *right_parent = tree_parent(root->right, val, element_size);
  if (right_parent) {
    return right_parent;
  }

  return tree_parent(root->left, val, element_size);
}

void tree_insert(Tree *tree, void *val) {
  ASSERT(val, "Null item passed to tree_insert\n");

  TreeNode *node = treenode_create(val, NULL, NULL, tree->element_size);

  if (tree->root == NULL) {
    tree->root = node;
    return;
  }

  Queue *q = queue_create(DataType_TREENODE);
  enqueue(q, &(tree->root));
  while (q->front) {
    TreeNode *current = *(TreeNode **)dequeue(q);
    if (memcmp(current->value, node->value, tree->element_size) == 0) {
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

static void tree_helper_delete(TreeNode *root, TreeNode **lastptr,
                               TreeNode **itemptr, void *val,
                               size_t element_size) {
  if (!root)
    return;

  if (memcmp(root->value, val, element_size) == 0)
    *itemptr = root;

  tree_helper_delete(root->left, lastptr, itemptr, val, element_size);
  *lastptr = root;
  tree_helper_delete(root->right, lastptr, itemptr, val, element_size);
}

void tree_delete(Tree *tree, void *val) {
  TreeNode *lastptr = NULL, *itemptr = NULL, *parentptr = NULL;

  tree_helper_delete(tree->root, &lastptr, &itemptr, val, tree->element_size);

  if (itemptr && lastptr)
    memcpy(itemptr->value, lastptr->value, tree->element_size);

  parentptr = tree_parent(tree->root, lastptr->value, tree->element_size);

  if (parentptr->right == lastptr)
    parentptr->right = NULL;
  else
    parentptr->left = NULL;

  free(lastptr->value);
  free(lastptr);
}

TreeNode *search_tree_node(TreeNode *node, void *val, size_t element_size) {
  if (node == NULL)
    return NULL;

  TreeNode *left_node = search_tree_node(node->left, val, element_size);
  if (left_node)
    return left_node;

  if (memcmp(node->value, val, element_size) == 0) {
    return node;
  }

  return search_tree_node(node->right, val, element_size);
}
