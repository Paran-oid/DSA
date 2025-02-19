#include "funcs.h"
#include "linked.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *arg1, void *arg2, enum datatype type) {
  usize item_size = type_map(type);
  char temp[item_size];
  memmove(temp, arg1, item_size);
  memmove(arg1, arg2, item_size);
  memmove(arg2, temp, item_size);
}

// TODO: make a number comparer (double int, float ...)
// TODO: make a general printer for each data type
usize type_map(enum datatype type) {
  switch (type) {
  case CHAR:
    return sizeof(char);
  case INT:
    return sizeof(i32);
  case FLOAT:
    return sizeof(f32);
  case DOUBLE:
    return sizeof(f64);
  case STRING:
    return sizeof(char *);
  case PAIR:
    return sizeof(pair_t);
  case NODE:
    return sizeof(listnode_t);
  case TREENODE:
    return sizeof(treenode_t);
  default:
    return 0;
  }
}