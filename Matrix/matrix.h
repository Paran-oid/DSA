#pragma once

#include "models.h"

// Matrix createialization & Destruction
Matrix mat_create(size_t rows, size_t cols, DataType type);
void mat_fill(Matrix *mat, const void *arr, size_t n);
void mat_destroy(Matrix *mat);

// Matrix Operations
int mat_det(const Matrix *mat);
Matrix mat_add(const Matrix *mat1, const Matrix *mat2);
Matrix mat_mult(const Matrix *mat1, const Matrix *mat2);
// void mat_rot(Matrix *mat);

// LEETCODE SECTION
