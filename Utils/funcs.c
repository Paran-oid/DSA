#include "funcs.h"
#include "models.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

void swap(void *arg1, void *arg2, DataType type) {
  size_t item_size = type_map(type);
  if (item_size == 0)
    return; // Safety check

  void *temp = malloc(item_size);
  if (!temp) {
    fprintf(stderr, "Memory allocation failed in swap()\n");
    exit(EXIT_FAILURE);
  }

  memmove(temp, arg1, item_size);
  memmove(arg1, arg2, item_size);
  memmove(arg2, temp, item_size);

  free(temp);
}

// TODO: make a number comparer (double, int, float ...)
// TODO: make a general printer for each data type
size_t type_map(DataType type) {
  switch (type) {
  case DATATYPE_CHAR:
    return sizeof(char);
  case DATATYPE_INT:
    return sizeof(int);
  case DATATYPE_FLOAT:
    return sizeof(float);
  case DATATYPE_DOUBLE:
    return sizeof(double);
  case DATATYPE_STRING:
    return sizeof(char *); // String is a pointer
  case DATATYPE_PAIR:
    return sizeof(Pair); // Struct, not pointer
  case DATATYPE_NODE:
    return sizeof(ListNode);
  case DataType_TREENODE:
    return sizeof(TreeNode);
  default:
    return 0;
  }
}
