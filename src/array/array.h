#ifndef ARRAY
#define ARRAY

#include "stdlib.h"
#include "string.h"

typedef struct array_t {
  void *data;
  unsigned long element_size;
  int count;
} array;

int array_init(array *arr, int count, unsigned long size);
int array_free(array *arr);

void *array_get(array *arr, int index);
int array_put(array *arr, int index, const void *data);
#endif
