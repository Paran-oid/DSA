#include "array.h"
#include "funcs.h"
#include "logs.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inord_trav(treenode_t *root) {
  if (root == NULL)
    return;

  printf("%s ", (char *)root->val);
  inord_trav(root->left);
  inord_trav(root->right);
}

int main(void) {

  logger_create(ALL);

  // LEARN ABOUT BITFIELDS

  tree_t *mytree = tree_create(STRING);
  char *vals[] = {"aziz", "yo", "damn"};
  for (usize i = 0; i < 3; i++) {
    tree_insert(mytree, vals[i]);
  }

  inord_trav(mytree->root);

  tree_destroy(mytree);

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TESTS