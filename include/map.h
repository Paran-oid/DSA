#pragma once

#include "funcs.h"

typedef struct map {
  pair_t *items;
  usize size;
  usize capacity;
} map_t;