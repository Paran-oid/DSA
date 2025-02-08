#pragma once

#include <stddef.h>

typedef struct {
  size_t cols;
  size_t rows;
  int **items;
} Matrix;

Matrix init_mat(int rows, int cols);
// TODO
void print_mat(Matrix *mat);
void destroy_mat(Matrix *mat);

Matrix add_mat(Matrix *mat1, Matrix *mat2);
Matrix mult_mat(Matrix *mat1, Matrix *mat2);
void rot_mat(Matrix *mat);

// LEETCODE SECTION
