#pragma once

#include "funcs.h"

#include <stddef.h>

typedef struct {
  size_t cols;
  size_t rows;
  i32 **items;
} Matrix;

Matrix init_mat(usize rows, usize cols);
void fill_mat(Matrix *mat, i32 *arr, usize n);
void print_mat(Matrix *mat);
void destroy_mat(Matrix *mat);

i32 det_mat(Matrix *mat);

Matrix add_mat(Matrix *mat1, Matrix *mat2);
Matrix mult_mat(Matrix *mat1, Matrix *mat2);
void rot_mat(Matrix *mat);

// LEETCODE SECTION
