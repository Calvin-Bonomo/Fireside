#ifndef HEAP
#define HEAP

#include "stdlib.h"

typedef uint (*heapCompareFunc)(void *left, void *right);

typedef struct {
  void **data;
  unsigned int count;
  unsigned int maxCount;
  heapCompareFunc compare;
} Heap;

int heap_init(Heap *heap, ulong count, heapCompareFunc compare);

int heap_free(Heap *heap);

int heap_push(Heap *heap, void *data);

void *heap_pop(Heap *heap);

void *heap_peek(Heap *heap);

#endif
