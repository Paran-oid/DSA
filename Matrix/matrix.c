#include "matrix.h"
#include "funcs.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix mat_create(size_t rows, size_t cols, DataType type) {

  Matrix mat;

  mat.rows = rows;
  mat.cols = cols;
  mat.element_size = type_map(type);
  mat.type = type;

  mat.items = malloc(sizeof(void *) * mat.rows);
  for (size_t i = 0; i < mat.rows; i++) {
    mat.items[i] = malloc(mat.element_size * mat.cols);
  }
  return mat;
}

void mat_fill(Matrix *mat, const void *arr, size_t n) {
  size_t k = 0;
  ASSERT(n <= (mat->rows * mat->cols),
         "Can't fill matrix with this array...\n");

  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      memcpy((char *)mat->items[i] + (j * mat->element_size),
             (char *)arr + k * mat->element_size, mat->element_size);
      k++;
    }
  }
}

void mat_destroy(Matrix *mat) {

  for (size_t i = 0; i < mat->rows; i++) {
    free(mat->items[i]);
  }
  free(mat->items);
}

int mat_det(const Matrix *mat) {
  ASSERT(mat->element_size == type_map(DATATYPE_INT),
         "Matrix must have integers...\n");
  ASSERT(mat->cols == mat->rows,
         "Matrix must be square to compute determinant.\n");

  int **mymat = (int **)mat->items;
  int res = 0;

  if (mat->cols == 2) {
    res = mymat[0][0] * mymat[1][1] - mymat[0][1] * mymat[1][0];
  } else if (mat->cols == 3) {
    uint8_t sig = 1;

    for (size_t i = 0; i < 3; i++) {
      int minorDet = mymat[1][(i + 1) % 3] * mymat[2][(i + 2) % 3] -
                     mymat[1][(i + 2) % 3] * mymat[2][(i + 1) % 3];

      res += sig * mymat[0][i] * minorDet;
      sig = -sig;
    }
  }
  return res;
}

Matrix mat_add(const Matrix *mat1, const Matrix *mat2) {
  ASSERT(mat1->element_size == type_map(DATATYPE_INT) &&
             mat2->element_size == type_map(DATATYPE_INT),
         "Matrix must have integers...\n");

  if ((mat1->rows != mat2->rows) || (mat1->cols != mat2->cols)) {
    perror("Matrices must have the same number of rows and columns.");
    exit(EXIT_FAILURE);
  }

  Matrix res = mat_create(mat1->rows, mat1->cols, mat1->element_size);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat1->cols; j++) {
      ((int *)res.items[i])[j] =
          ((int *)mat1->items[i])[j] + ((int *)mat2->items[i])[j];
    }
  }

  return res;
}

Matrix mat_mult(const Matrix *mat1, const Matrix *mat2) {
  ASSERT(mat1->cols == mat2->rows,
         "Matrix multiplication requires the number of columns in the first "
         "matrix "
         "to match the number of rows in the second matrix.");

  Matrix res = mat_create(mat1->rows, mat2->cols, mat1->element_size);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat2->cols; j++) {
      int sum = 0;
      for (size_t k = 0; k < mat1->cols; k++) {
        sum += ((int *)mat1->items[i])[k] * ((int *)mat2->items[k])[j];
      }
      ((int *)res.items[i])[j] = sum;
    }
  }

  return res;
}

// TODO
// void mat_rot(Matrix *mat) {}
