#include "heap.h"

int heap_init(Heap *heap, unsigned long dataSize, unsigned int initialHeapSize) {
  if (!heap || !dataSize || !initialHeapSize) return -1;

  if (!(heap->data = malloc(dataSize * initialHeapSize))) return -1;
  heap->count = 0;
  heap->maxCount = initialHeapSize;
  heap->dataSize = dataSize;

  return 0;
}

int heap_free(Heap *heap) {
  if (!heap) return -1;
  free(heap->data);

  return 0;
}

int heap_add(Heap *heap, void *data, unsigned long dataSize) {
  if (!heap || !data || dataSize != heap->dataSize) return -1;
  if (heap->count == heap->maxCount) { // Reallocate array
    if (heap->maxCount > 2 * heap->maxCount) return -1; // Unsigned overflow

    void *newData = malloc(2 * heap->maxCount);
    if (!newData || !copy(heap->data, newData, dataSize * heap->maxCount)) return -1;
    
    free(heap->data);
    heap->maxCount *= 2;
    heap->data = newData;
  }

  uint dataIndex = heap->count++, parentIndex;
  void *parent, *child;
  if (!copy(data, heap + dataIndex * dataSize, dataSize)) return -1;

  while (dataIndex) {
    parentIndex = (dataIndex - (dataIndex % 2)) / 2;
    parent = heap->data + parentIndex * dataSize;
    child = heap->data + dataIndex * dataSize;
    
    if (!heap->compare(parent, child)) break;

    if (!swap(parent, child, dataSize)) return -1;
    dataIndex = parentIndex;
  }

  return 0;
}

int heap_get_max(Heap *heap) {

}
