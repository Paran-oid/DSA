#include "funcs.h"
#include "logs.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

  init_logger(ALL);

  Matrix mat = init_mat(3, 3);
  i32 arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fill_mat(&mat, arr, sizeof(arr) / sizeof(arr[0]));
  print_mat(&mat);

  destroy_logger();

  exit(EXIT_SUCCESS);
}