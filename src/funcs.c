#include "funcs.h"

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
  }
}