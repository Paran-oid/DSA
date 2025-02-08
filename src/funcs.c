#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *arg1, void *arg2, usize item_size) {
  char temp[item_size];
  memmove(temp, arg1, item_size);
  memmove(arg1, arg2, item_size);
  memmove(arg2, temp, item_size);
}