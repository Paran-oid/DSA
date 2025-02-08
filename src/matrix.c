#include "matrix.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>

Matrix init_mat(int rows, int cols) {

  Matrix mat;

  mat.rows = rows;
  mat.cols = cols;

  mat.items = malloc(sizeof(int *) * mat.rows);
  for (size_t i = 0; i < mat.rows; i++) {
    mat.items[i] = malloc(sizeof(int) * mat.cols);
  }
  return mat;
}

void destroy_mat(Matrix *mat) {
  if (!mat)
    return;

  for (size_t i = 0; i < mat->rows; i++) {
    free(mat->items[i]);
  }
  free(mat->items);
  free(mat);
}

Matrix add_mat(Matrix *mat1, Matrix *mat2) {
  if ((mat1->rows != mat2->rows) || (mat1->cols != mat2->cols)) {
    perror("matrixes must have same num of rows and cols");
    exit(EXIT_FAILURE);
  }

  Matrix res = init_mat(mat1->rows, mat1->cols);

  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat2->rows; j++) {
      res.items[i][j] = mat1->items[i][j] + mat2->items[i][j];
    }
  }

  return res;
}

Matrix mult_mat(Matrix *mat1, Matrix *mat2) {
  if (mat1->rows != mat2->cols) {
  }
  Matrix res = init_mat(mat1->cols, mat2->rows);
  for (size_t k = 0; k < mat1->cols; k++) {
    for (size_t i = 0; i < mat1->cols; i++) {
      for (size_t j = 0; j < mat2->rows; j++) {
        res.items[k][i] += mat1->items[k][j] * mat2->items[j][i];
      }
    }
  }
  return res;
}

// TODO
void rot_mat(Matrix *mat) {}