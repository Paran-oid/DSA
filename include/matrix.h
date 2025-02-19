#pragma once

#include "funcs.h"
#include <stddef.h>

typedef struct matrix {
  void **items;
  usize rows, cols, tsize;
  enum datatype type;
} matrix_t;

// Matrix Initialization & Destruction
matrix_t mat_init(usize rows, usize cols, enum datatype type);
void mat_fill(matrix_t *mat, const void *arr, usize n);
void mat_destroy(matrix_t *mat);

// Matrix Operations
i32 mat_det(const matrix_t *mat);
matrix_t mat_add(const matrix_t *mat1, const matrix_t *mat2);
matrix_t mat_mult(const matrix_t *mat1, const matrix_t *mat2);
// void mat_rot(matrix_t *mat);

// LEETCODE SECTION
