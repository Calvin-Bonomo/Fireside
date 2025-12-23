#ifndef TEST_HEAP
#define TEST_HEAP

#define HEAP_TEST_SIZE 10000

#include "heap.h"
#include "assert.h"

void test_heap();

void test_heap_init();
void test_heap_free();

void test_heap_push();
void test_heap_pop();
void test_heap_peek();

#endif