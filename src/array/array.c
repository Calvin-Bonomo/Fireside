#include "array.h"

int array_init(array *arr, int count, unsigned long size) 
{
  if (!arr || count < 0 || !size) return -1;

  arr->data = malloc(count * size);
  if (!arr->data) return -2;
  arr->count = count;
  arr->element_size = size;
  return 0;
}

int array_free(array *arr) 
{
  if (!arr) return -1;
  free(arr->data);
  return 0;
}

void *array_get(array *arr, int index) 
{
  if (!arr || index < 0 || index >= arr->count) return NULL;

  return arr->data + (index * arr->element_size);
}

int array_put(array *arr, int index, const void *data) 
{
  if (!arr || !data || index < 0 || index >= arr->count) return -1;

  if (!memcpy(arr->data + (arr->element_size * index), data, arr->element_size)) return -2;
  
  return 0;
}
