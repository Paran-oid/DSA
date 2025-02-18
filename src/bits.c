#include "funcs.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

usize bit_extract(usize num, usize pos) {
  usize mask = 1 << pos;
  return (mask & num) >> pos;
}
usize bits_extract(usize num, usize l, usize r) {
  usize mask = 0;
  for (usize i = l; i <= r; i++) {
    mask = mask | (1 << i);
  }

  return (mask & num) >> l;
}

usize bit_set(usize num, usize pos) {
  usize mask = 1 << pos;
  return num | mask;
}
usize bits_set(usize num, usize l, usize r) {
  i32 mask = 0;
  for (usize i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num | mask;
}

usize bit_clear(usize num, usize pos) {
  i32 mask = ~(1 << pos);
  return mask & num;
}
usize bits_clear(usize num, usize l, usize r) {
  i32 mask = ~0;
  for (usize i = l; i < r; i++) {
    mask = mask | ~(1 << i);
  }

  return mask & num;
}

usize bit_toggle(usize num, usize pos) {
  i32 mask = 1 << pos;
  return num ^ mask;
}
usize bits_toggle(usize num, usize l, usize r) {
  i32 mask = 0;
  for (usize i = l; i < r; i++) {
    mask = mask | (1 << i);
  }

  return num ^ mask;
}

i32 bits_count(usize num) {
  i32 count = 0;
  while (num) {
    count += num & 1;
    num >>= 1;
  }
  return count;
}

void bits_print_binary(usize num) {
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