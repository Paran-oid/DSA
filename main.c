#include "funcs.h"
#include "logs.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  logger_init(ALL);

  i32 x = 3;
  i32 y = 4;
  i32 z = 5;
  i32 a = 6;
  i32 b = 7;
  i32 c = 8;

  tree_t *tree = tree_init(INT);
  tree_insert(tree, &x);
  tree_insert(tree, &y);
  tree_insert(tree, &z);
  tree_insert(tree, &a);
  tree_insert(tree, &b);
  tree_insert(tree, &c);

  printf("value of root is %d\n", *(i32 *)tree->root->right->left->val);

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TEST