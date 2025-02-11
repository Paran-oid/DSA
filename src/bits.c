#include "funcs.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

usize extract_bit(usize num, size_t pos) {
  usize mask = 1 << pos;
  return (mask & num) >> pos;
}
usize extract_bits(usize num, usize l, usize r) {
  usize mask = 0;
  for (size_t i = l; i <= r; i++) {
    mask = mask | (1 << i);
  }

  return (mask & num) >> l;
}

usize set_bit(usize num, size_t pos) {
  usize mask = 1 << pos;
  return num | mask;
}
usize set_bits(usize num, usize l, usize r) {
  i32 mask = 0;
  for (size_t i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num | mask;
}

usize clear_bit(usize num, size_t pos) {
  i32 mask = ~(1 << pos);
  return mask & num;
}
usize clear_bits(usize num, usize l, usize r) {
  i32 mask = ~0;
  for (size_t i = l; i < r; i++) {
    mask = mask | ~(1 << i);
  }

  return mask & num;
}

usize toggle_bit(usize num, size_t pos) {
  i32 mask = 1 << pos;
  return num ^ mask;
}
usize toggle_bits(usize num, usize l, usize r) {
  i32 mask = 0;
  for (size_t i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num ^ mask;
}

i32 count_bits(usize num) {
  i32 count = 0;
  while (num) {
    count += num & 1;
    num >>= 1;
  }
  return count;
}

void print_binary(usize num) {
  i32 num_bits = sizeof(i32) * __CHAR_BIT__;

  usize mask = 1 << (num_bits - 1);

  while (mask && !(num & mask)) {
    mask >>= 1;
  }

  while (mask) {
    printf("%d", (num & mask) ? 1 : 0);
    mask >>= 1;
  }
  printf("\n");
}