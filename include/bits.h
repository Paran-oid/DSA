#pragma once

#include <funcs.h>

usize bit_extract(usize num, usize pos);
usize bits_extract(usize num, usize l, usize r);

usize bit_set(usize num, usize pos);
usize bits_set(usize num, usize l, usize r);

usize bit_clear(usize num, usize pos);
usize bits_clear(usize num, usize l, usize r);

usize bit_toggle(usize num, usize pos);
usize bits_toggle(usize num, usize l, usize r);

usize bits_count(usize num);

void bits_print_binary(usize num);

// TODO: make sure I check every malloc was successful
// TODO: make it print negative binaries too
// LEETCODE SECTION
