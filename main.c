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


  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TESTS