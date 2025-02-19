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

// TODO: Make a solution for matrix of any order N
i32 mat_det(const matrix_t *mat) {
  ASSERT(mat->tsize == type_map(INT), "Matrix must have integers...\n");
  ASSERT(mat->cols == mat->rows, "Invalid matrix...\n");
  ASSERT(mat->cols == 3 || mat->cols == 2,
         "Can't calculate det of this matrix...\n");

  if (mat->rows != mat->cols) {
    printf("Matrix must be square to compute determinant.\n");
    return 0;
  }

  i32 res = 0;

  if (mat->cols == 2) {
    res = (*(i32 *)mat->items[0] * *(i32 *)mat->items[3]) -
          (*(i32 *)mat->items[1] * *(i32 *)mat->items[2]);
  } else if (mat->cols == 3) {
    i8 sig = 1;
    pair_t cordsArr[4];

    for (usize i = 0; i < 3; i++) {
      i32 tempRes = sig * *(i32 *)((char *)mat->items + (i * mat->tsize));
      sig = -sig;

      cordsArr[0] =
          (pair_t){(char *)mat->items + (1 * mat->tsize),
                   (char *)mat->items + ((i + 1) % 3 * mat->tsize), mat->tsize};
      cordsArr[1] =
          (pair_t){(char *)mat->items + (1 * mat->tsize),
                   (char *)mat->items + ((i + 2) % 3 * mat->tsize), mat->tsize};
      cordsArr[2] =
          (pair_t){(char *)mat->items + (2 * mat->tsize),
                   (char *)mat->items + ((i + 1) % 3 * mat->tsize), mat->tsize};
      cordsArr[3] =
          (pair_t){(char *)mat->items + (2 * mat->tsize),
                   (char *)mat->items + ((i + 2) % 3 * mat->tsize), mat->tsize};

      i32 minorDet = (*(i32 *)cordsArr[0].first * *(i32 *)cordsArr[3].second) -
                     (*(i32 *)cordsArr[1].first * *(i32 *)cordsArr[2].second);

      tempRes *= minorDet;
      res += tempRes;
      sig = -sig;
    }
  }

  return res;
}

matrix_t mat_add(const matrix_t *mat1, const matrix_t *mat2) {
  ASSERT(mat1->tsize == type_map(INT) && mat2->tsize == type_map(INT),
         "Matrix must have integers...\n");

  if ((mat1->rows != mat2->rows) || (mat1->cols != mat2->cols)) {
    perror("matrixes must have same num of rows and cols");
    exit(EXIT_FAILURE);
  }

  matrix_t res = mat_init(mat1->rows, mat1->cols, mat1->tsize);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat2->rows; j++) {
      ((i32 *)res.items[i])[j] =
          ((i32 *)mat1->items[i])[j] + ((i32 *)mat2->items[i])[j];
    }
  }

  return res;
}

matrix_t mat_mult(const matrix_t *mat1, const matrix_t *mat2) {
  ASSERT(mat1->rows == mat2->cols,
         "Inputed Matrixes for multiplication must have the numbers of the "
         "first's rows same as second's columns");

  matrix_t res = mat_init(mat1->cols, mat2->rows, mat1->tsize);
  for (size_t k = 0; k < mat1->cols; k++) {
    for (size_t i = 0; i < mat1->cols; i++) {
      for (size_t j = 0; j < mat2->rows; j++) {
        ((i32 *)(res.items)[k])[i] +=
            ((i32 *)mat1->items[k])[j] * ((i32 *)mat2->items[j])[i];
      }
    }
  }
  return res;
}

// TODO
// void mat_rot(matrix_t *mat) {}