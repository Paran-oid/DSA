#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(_e, ...)                                                        \
  do {                                                                         \
    if (!(_e)) {                                                               \
      fprintf(stderr, __VA_ARGS__);                                            \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

void data_destroy(void *data);

#endif