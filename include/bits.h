#pragma once

#include <funcs.h>

usize extract_bit(usize num, usize pos);
usize extract_bits(usize num, usize l, usize r);

usize set_bit(usize num, usize pos);
usize set_bits(usize num, usize l, usize r);

usize clear_bit(usize num);
usize clear_bits(usize num, u32 l, u32 r);

usize toggle_bit(usize num, usize pos);
usize toggle_bits(usize num, u32 l, u32 r);

i32 count_bits(usize num);
// TODO: make sure I check every malloc was successful
// TODO: make it print negative binaries too
void print_binary(i32 num);

// LEETCODE SECTION
