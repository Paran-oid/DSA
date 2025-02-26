#pragma once

#include "models.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ASSERT(_e, ...)                                                        \
  do {                                                                         \
    if (!(_e)) {                                                               \
      fprintf(stderr, __VA_ARGS__);                                            \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

size_t type_map(DataType type);
DataType to_type(size_t size);
void swap(void *arg1, void *arg2, DataType type);
