#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"

typedef struct {
    void *data;
    uint elementSize;
    uint count;
} array;

// Initialize an array, `arr`, with `n` elements of size `s`
int array_init(array *arr, uint n, uint s);

// Free an array, `arr`
void array_free(array *arr);

// Get an element from `arr` at index, `i`
void *array_get(array *arr, uint i);

// Set an element in `arr` to `val` at index, `i`
void array_set(array *arr, void *val, uint i);

#endif
