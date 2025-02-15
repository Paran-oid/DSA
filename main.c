#include "funcs.h"
#include "logs.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

  init_logger(ALL);

  TreeNode *node1 = init_tree_node(10);

  insert_tree_node(node1, 20);
  insert_tree_node(node1, 50);
  insert_tree_node(node1, 100);
  insert_tree_node(node1, 200);

  print_tree(node1, INORD);

  destroy_tree_node(node1);
  destroy_logger();
  exit(EXIT_SUCCESS);
}