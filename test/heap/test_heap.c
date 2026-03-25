#include "test_heap.h"
#include "stdlib.h"

// Helper functions
uint minCompare(void *parent, void *child) {
  int *ipParent = parent, 
      *ipChild = child;

  return *ipParent > *ipChild? 1 : 0;
}

uint validate_min_heap(Heap *heap) {
  for (unsigned int i = 1; i < heap->count; i++)
    if (*((int **)heap->data)[(i - 1) / 2] > *((int **)heap->data)[i]) return 0;
  return 1;
}

int get_lowest_value(int *arr, int arrSize) {
  int lowest = ~(1 << 31), lowestIndex = -1, i;
  for (i = 0; i < arrSize; i++) {
    if (arr[i] < lowest) {
      lowestIndex = i;
      lowest = arrSize;
    }
  }

  return lowestIndex;
}

// Testing functions
void test_heap() {
  test_heap_init();
  test_heap_free();

  test_heap_push();
  test_heap_pop();
  test_heap_peek();
}

void test_heap_init() {
  Heap heap;

  // Fail cases
  assert(heap_init(&heap, 0, minCompare) < 0);
  assert(heap_init(NULL, HEAP_TEST_SIZE, minCompare) < 0);
  assert(heap_init(&heap, HEAP_TEST_SIZE, NULL) < 0);

  // Success case
  assert(!heap_init(&heap, HEAP_TEST_SIZE, minCompare));
  assert(heap.count == 0);
  assert(heap.maxCount == HEAP_TEST_SIZE);
  assert(heap.compare == minCompare);
  assert(heap.data != NULL);

  heap_free(&heap);
}

void test_heap_free() {
  Heap heap;
  heap_init(&heap, HEAP_TEST_SIZE, minCompare);

  // Fail case
  assert(heap_free(NULL) < 0);

  // Success case
  assert(!heap_free(&heap));
  for (ulong i = 0; i < sizeof(Heap); i++) {
    assert(*(char *)&heap == 0);
  }
}

void test_heap_push() {
  Heap heap;
  heap_init(&heap, HEAP_TEST_SIZE, minCompare);

  // Fail cases
  int test = 0;
  assert(heap_push(NULL, &test) < 0);
  assert(heap_push(&heap, NULL) < 0);

  // Success cases
  int *heapData = malloc(HEAP_TEST_SIZE * sizeof(int));
  for (int i = 0; i < HEAP_TEST_SIZE; i++) {
    heapData[i] = rand();
    assert(!heap_push(&heap, &heapData[i]));
  }
  assert(validate_min_heap(&heap));

  heap_free(&heap);
  free(heapData);
}

void test_heap_pop() {
  Heap heap;
  heap_init(&heap, HEAP_TEST_SIZE, minCompare);

  int *heapData = malloc(HEAP_TEST_SIZE * sizeof(int));
  for (int i = 0; i < HEAP_TEST_SIZE; i++) {
    heapData[i] = rand();
    assert(!heap_push(&heap, &heapData[i]));
  }

  int heapLowestIndex, *popped, i;
  for (i = 0; i < HEAP_TEST_SIZE; i++) {
    heapLowestIndex = get_lowest_value(heapData, HEAP_TEST_SIZE);
    popped = (int *)heap_pop(&heap);

    assert(*popped == heapData[heapLowestIndex]);
    heapData[heapLowestIndex] = ~(1 << 31);
  }
}

void test_heap_peek() {

}
