#include "tree.h"
#include "funcs.h"
#include "lqueue.h"

static void inorder_traversal(TreeNode *node) {
  if (node == NULL)
    return;

  inorder_traversal(node->left);

  printf("%d, ", node->val);

  inorder_traversal(node->right);
}
static void preorder_traversal(TreeNode *node) {
  if (node == NULL)
    return;

  printf("%d, ", node->val);

  preorder_traversal(node->left);

  preorder_traversal(node->right);
}
static void postorder_traversal(TreeNode *node) {
  if (node == NULL)
    return;

  postorder_traversal(node->left);

  postorder_traversal(node->right);

  printf("%d, ", node->val);
}
// FIXME
static void levelorder_traversal(TreeNode *node) {
  LQueue *q = init_lqueue((i32)(intptr_t)node);
  while (q->front != NULL) {
    TreeNode *extracted_node = (TreeNode *)(intptr_t)dequeue_lqueue(&q);
    printf("%d, ", extracted_node->val);

    if (extracted_node->left) {
      enqeue_lqueue(&q, (i32)(intptr_t)extracted_node->left);
    }
    if (extracted_node->right) {
      enqeue_lqueue(&q, (i32)(intptr_t)extracted_node->right);
    }
  }
}

TreeNode *init_tree_node(i32 val) {
  TreeNode *myNode = (TreeNode *)malloc(sizeof(TreeNode));
  myNode->left = NULL;
  myNode->right = NULL;
  myNode->val = val;

  return myNode;
}
void print_tree(TreeNode *node, TraverseMode mode) {
  switch (mode) {
  case INORD:
    inorder_traversal(node);
    break;
  case PRE:
    preorder_traversal(node);
    break;
  case POST:
    postorder_traversal(node);
    break;
  case LEVEL:
    levelorder_traversal(node);
    break;
  }
}
void destroy_tree_node(TreeNode *node) {
  if (node == NULL) {
    return;
  }

  destroy_tree_node(node->right);
  destroy_tree_node(node->left);

  free(node);
}

// void insert_tree_node(TreeNode *node, i32 val) {
// }
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