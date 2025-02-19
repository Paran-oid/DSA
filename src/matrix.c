#include "matrix.h"
#include "funcs.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrix_t mat_init(usize rows, usize cols, enum datatype type) {

  matrix_t mat;

  mat.rows = rows;
  mat.cols = cols;
  mat.tsize = type_map(type);
  mat.type = type;

  mat.items = malloc(sizeof(void *) * mat.rows);
  for (size_t i = 0; i < mat.rows; i++) {
    mat.items[i] = malloc(mat.tsize * mat.cols);
  }
  return mat;
}

void mat_fill(matrix_t *mat, const void *arr, usize n) {
  usize k = 0;
  ASSERT(n <= (mat->rows * mat->cols),
         "Can't fill matrix with this array...\n");

  for (usize i = 0; i < mat->rows; i++) {
    for (usize j = 0; j < mat->cols; j++) {
      memcpy((char *)mat->items[i] + (j * mat->tsize),
             (char *)arr + k * mat->tsize, mat->tsize);
      k++;
    }
  }
}

void mat_destroy(matrix_t *mat) {

  for (size_t i = 0; i < mat->rows; i++) {
    free(mat->items[i]);
  }
  free(mat->items);
}

i32 mat_det(const matrix_t *mat) {
  ASSERT(mat->tsize == type_map(INT), "Matrix must have integers...\n");
  ASSERT(mat->cols == mat->rows,
         "Matrix must be square to compute determinant.\n");

  i32 **mymat = (i32 **)mat->items;
  i32 res = 0;

  if (mat->cols == 2) {
    res = mymat[0][0] * mymat[1][1] - mymat[0][1] * mymat[1][0];
  } else if (mat->cols == 3) {
    i8 sig = 1;

    for (usize i = 0; i < 3; i++) {
      i32 minorDet = mymat[1][(i + 1) % 3] * mymat[2][(i + 2) % 3] -
                     mymat[1][(i + 2) % 3] * mymat[2][(i + 1) % 3];

      res += sig * mymat[0][i] * minorDet;
      sig = -sig;
    }
  }
  return res;
}

matrix_t mat_add(const matrix_t *mat1, const matrix_t *mat2) {
  ASSERT(mat1->tsize == type_map(INT) && mat2->tsize == type_map(INT),
         "Matrix must have integers...\n");

  if ((mat1->rows != mat2->rows) || (mat1->cols != mat2->cols)) {
    perror("Matrices must have the same number of rows and columns.");
    exit(EXIT_FAILURE);
  }

  matrix_t res = mat_init(mat1->rows, mat1->cols, mat1->tsize);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat1->cols; j++) {
      ((i32 *)res.items[i])[j] =
          ((i32 *)mat1->items[i])[j] + ((i32 *)mat2->items[i])[j];
    }
  }

  return res;
}

matrix_t mat_mult(const matrix_t *mat1, const matrix_t *mat2) {
  ASSERT(mat1->cols == mat2->rows,
         "Matrix multiplication requires the number of columns in the first "
         "matrix "
         "to match the number of rows in the second matrix.");

  matrix_t res = mat_init(mat1->rows, mat2->cols, mat1->tsize);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat2->cols; j++) {
      i32 sum = 0;
      for (size_t k = 0; k < mat1->cols; k++) {
        sum += ((i32 *)mat1->items[i])[k] * ((i32 *)mat2->items[k])[j];
      }
      ((i32 *)res.items[i])[j] = sum;
    }
  }

  return res;
}

// TODO
// void mat_rot(matrix_t *mat) {}