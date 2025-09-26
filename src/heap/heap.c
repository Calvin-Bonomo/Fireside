#include "heap.h"
#include "utils.h"

int heap_init(Heap *heap, ulong count, heapCompareFunc compare) {
  if (!heap || !count || !compare) return -1;

  if (!(heap->data = malloc(sizeof(void *) * count))) return -1;
  heap->count = 0;
  heap->maxCount = count;
  heap->compare = compare;

  return 0;
}

int heap_free(Heap *heap) {
  if (!heap) return -1;
  free(heap->data);
  if (!clear(heap, sizeof(Heap *))) return -1;

  return 0;
}

int heap_push(Heap *heap, void *data) {
  if (!heap || !data) return -1;
  if (heap->count == heap->maxCount) { // Reallocate array for size-up
    if (heap->maxCount > 2 * heap->maxCount) return -1; // Unsigned overflow (heap is too big)

    void *newData = malloc(2 * heap->maxCount);
    if (!newData) return -1;
    if (!copy(heap->data, newData, sizeof(void *) * heap->maxCount)) {
      free(newData);
      return -1;
    }
    
    free(heap->data);
    heap->maxCount *= 2;
    heap->data = newData;
  }

  uint index = heap->count++,
       parentIndex = (index - 1) / 2;
  if (!copy(data, heap->data + index, sizeof(void *))) return -1;
  if (parentIndex >= index) return 0; // Heap was previously empty

  // Swap child and parent nodes until condition satisfied
  while (heap->compare(heap->data + index, heap->data + parentIndex) > 0) {
    if (!swap(heap->data + index, heap->data + parentIndex, sizeof(void *))) return -1;
    index = parentIndex;
    parentIndex = (index - 1) / 2;
  }

  return 0;
}

void *heap_pop(Heap *heap) {
  if (!heap || !heap->count) return NULL;
  void *oldRoot = NULL,
       *lastNode = heap->data + heap->count - 1;
  uint currentIndex = 0,
       replacementIndex = 0;

  if (!copy(heap->data, oldRoot, sizeof(void *))) return NULL;
  if (!copy(lastNode, heap->data, sizeof(void *))) return NULL;
  if (!clear(heap->data + (--heap->count), sizeof(void *))) return NULL;

  while (currentIndex < heap->count) {
    if (heap->compare(heap->data + currentIndex, heap->data + currentIndex * 2 + 1)) replacementIndex = currentIndex * 2 + 1;
    if (heap->compare(heap->data + currentIndex, heap->data + currentIndex * 2 + 2)) replacementIndex = currentIndex * 2 + 1;

    if (currentIndex == replacementIndex) break;
    if (!copy(heap->data + currentIndex, heap->data + replacementIndex, sizeof(void *))) return NULL;

    currentIndex = replacementIndex;
  }

  return oldRoot;
}

void *heap_peek(Heap *heap) {
  if (!heap || !heap->count) return NULL;
  return heap->data;
}
