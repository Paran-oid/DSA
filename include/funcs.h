#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef float f32;
typedef double f64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t usize;
typedef ssize_t isize;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ASSERT(_e, ...)                                                        \
  do {                                                                         \
    if (!(_e)) {                                                               \
      fprintf(stderr, __VA_ARGS__);                                            \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

typedef struct pair {
  void *first;
  void *second;
  usize type;
} pair_t;

enum datatype { CHAR, INT, FLOAT, DOUBLE, STRING };

usize type_map(enum datatype type);
void swap(void *arg1, void *arg2, enum datatype type);
