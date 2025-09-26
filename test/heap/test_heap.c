#include "test_heap.h"

// Helper functions
uint minCompare(void *left, void *right) {
  int *ipLeft = left, 
      *ipRight = right;
  return *ipRight - *ipLeft;
}

void test_heap() {
  test_heap_init();
  test_heap_free();
}

void test_heap_init() {
  Heap heap;

  // Fail cases
  assert(heap_init(&heap, 0, minCompare) < 0);
  assert(heap_init(NULL, 5, minCompare) < 0);
  assert(heap_init(&heap, 5, NULL) < 0);

  // Success case
  assert(!heap_init(&heap, 5, minCompare));
  assert(heap.count == 0);
  assert(heap.maxCount == 5);
  assert(heap.compare == minCompare);
  assert(heap.data != NULL);

  heap_free(&heap);
}

void test_heap_free() {
  Heap heap;
  heap_init(&heap, 5, minCompare);

  // Fail case
  assert(heap_free(NULL) < 0);

  // Success case
  assert(!heap_free(&heap));
  for (ulong i = 0; i < sizeof(Heap); i++) {
    assert(*(char *)&heap == 0);
  }
}