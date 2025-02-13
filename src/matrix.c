#include "matrix.h"
#include "funcs.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix init_mat(usize rows, usize cols) {

  Matrix mat;

  mat.rows = rows;
  mat.cols = cols;

  mat.items = malloc(sizeof(i32 *) * mat.rows);
  for (size_t i = 0; i < mat.rows; i++) {
    mat.items[i] = malloc(sizeof(i32) * mat.cols);
  }
  return mat;
}

void fill_mat(Matrix *mat, i32 *arr, usize n) {
  usize k = 0;
  ASSERT(n <= (mat->rows * mat->cols),
         "Can't fill matrix with this array...\n");
  for (usize i = 0; i < mat->rows; i++) {
    for (usize j = 0; j < mat->cols; j++) {
      mat->items[i][j] = arr[k++];
    }
  }
}

void print_mat(Matrix *mat) {
  printf("{\n ");
  for (usize i = 0; i < mat->rows; i++) {
    printf("{");
    for (usize j = 0; j < mat->cols; j++) {
      if (j == mat->cols - 1) {
        printf("%d", mat->items[i][j]);
      } else {
        printf("%d, ", mat->items[i][j]);
      }
    }
    if (i != mat->rows - 1)
      printf("},\n ");
    else {
      printf("}\n");
    }
  }
  printf("}\n");
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

// TODO: Make a solution for matrix of any order N
i32 det_mat(Matrix *mat) {
  ASSERT(mat->cols == mat->rows, "Invalid matrix...\n");
  ASSERT(mat->cols == 3 || mat->cols == 2,
         "Can't calculate det of this matrix...\n");

  i32 res = 0;

  Pair cordsArr[4];
  if (mat->cols == 2) {
    res = mat->items[0][0] * mat->items[1][1] -
          (mat->items[0][1] * mat->items[1][0]);
  } else if (mat->cols == 3) {
    i8 sig = 1;
    for (usize i = 0; i < 3; i++) {
      i32 tempRes = sig * mat->items[0][i];
      // I have no clue why this makes it work
      sig = -sig;

      cordsArr[0] = (Pair){1, (i + 1) % 3};
      cordsArr[1] = (Pair){1, (i + 2) % 3};
      cordsArr[2] = (Pair){2, (i + 1) % 3};
      cordsArr[3] = (Pair){2, (i + 2) % 3};

      i32 minorDet = mat->items[cordsArr[0].first][cordsArr[0].second] *
                         mat->items[cordsArr[3].first][cordsArr[3].second] -
                     mat->items[cordsArr[1].first][cordsArr[1].second] *
                         mat->items[cordsArr[2].first][cordsArr[2].second];

      tempRes *= minorDet;

      res += tempRes;
      sig = -sig;
    }
  }
  return res;
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
  ASSERT(mat1->rows == mat2->cols,
         "Inputed Matrixes for multiplication must have the numbers of the "
         "first's rows same as second's columns");

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