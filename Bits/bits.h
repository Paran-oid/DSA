#pragma once

typedef struct _size_t size_t;

size_t bit_extract(size_t num, size_t pos);
size_t bits_extract(size_t num, size_t l, size_t r);

size_t bit_set(size_t num, size_t pos);
size_t bits_set(size_t num, size_t l, size_t r);

size_t bit_clear(size_t num, size_t pos);
size_t bits_clear(size_t num, size_t l, size_t r);

size_t bit_toggle(size_t num, size_t pos);
size_t bits_toggle(size_t num, size_t l, size_t r);

size_t bits_count(size_t num);

void bits_print_binary(size_t num);

// TODO: make sure I check every malloc was successful
// TODO: make it print negative binaries too
// LEETCODE SECTION
