#ifndef UTILS_H
#define UTILS_H

#include "types.h"

// Copy `n` bytes at `src` to `dst`
void copy(void *src, void *dst, ulong n);

// Swap `n` bytes at `p1` with `p2`
int swap(void *p1, void *p2, ulong n);

// Set `n` bytes at `p` to 0
void clear(void *p, ulong n);

#endif
