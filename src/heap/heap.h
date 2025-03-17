#ifndef HEAP
#define HEAP

#include "stdlib.h"

typedef struct {
  void *data;
  unsigned long dataSize;
  unsigned int count;
  unsigned int maxCount;
} Heap;

int heap_init(Heap *heap, unsigned long dataSize, unsigned int initialHeapSize);

int heap_free(Heap *heap);

int heap_add(Heap *heap, void *data, unsigned long dataSize);

int heap_get_max(Heap *heap);

#endif
