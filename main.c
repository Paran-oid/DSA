#include "funcs.h"
#include "logs.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

  init_logger(ALL);

  Matrix mat1 = init_mat(3, 3);
  Matrix mat2 = init_mat(3, 3);

  i32 arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  fill_mat(&mat1, arr1, sizeof(arr1) / sizeof(arr1[0]));
  fill_mat(&mat2, arr1, sizeof(arr1) / sizeof(arr1[0]));

  print_mat(&mat1);

  printf("determinant of mat1 is %d \n", det_mat(&mat1));

  destroy_logger();
  exit(EXIT_SUCCESS);
}