#include "funcs.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

size_t bit_extract(size_t num, size_t pos) {
  size_t mask = 1 << pos;
  return (mask & num) >> pos;
}
size_t bits_extract(size_t num, size_t l, size_t r) {
  size_t mask = 0;
  for (size_t i = l; i <= r; i++) {
    mask = mask | (1 << i);
  }

  return (mask & num) >> l;
}

size_t bit_set(size_t num, size_t pos) {
  size_t mask = 1 << pos;
  return num | mask;
}
size_t bits_set(size_t num, size_t l, size_t r) {
  int mask = 0;
  for (size_t i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num | mask;
}

size_t bit_clear(size_t num, size_t pos) {
  int mask = ~(1 << pos);
  return mask & num;
}
size_t bits_clear(size_t num, size_t l, size_t r) {
  int mask = ~0;
  for (size_t i = l; i < r; i++) {
    mask = mask | ~(1 << i);
  }

  return mask & num;
}

size_t bit_toggle(size_t num, size_t pos) {
  int mask = 1 << pos;
  return num ^ mask;
}
size_t bits_toggle(size_t num, size_t l, size_t r) {
  int mask = 0;
  for (size_t i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num ^ mask;
}

int bits_count(size_t num) {
  int count = 0;
  while (num) {
    count += num & 1;
    num >>= 1;
  }
  return count;
}

void bits_print_binary(size_t num) {
  int num_bits = sizeof(int) * __CHAR_BIT__;

  size_t mask = 1 << (num_bits - 1);

  while (mask && !(num & mask)) {
    mask >>= 1;
  }

  while (mask) {
    printf("%d", (num & mask) ? 1 : 0);
    mask >>= 1;
  }
  printf("\n");
}