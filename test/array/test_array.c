#include "test_array.h"

void test_array() 
{
  test_array_init();
  test_array_free();
  test_array_put();
  test_array_get();
}

void test_array_init() 
{
  array intArr;
  int count = 5;
  unsigned long size = sizeof(int);
  
  assert(array_init(NULL, 5, 10) == -1);
  assert(array_init(&intArr, -1, size) == -1);
  assert(array_init(&intArr, count, 0) == -1);
  assert(array_init(&intArr, count, size) == 0);

  array_free(&intArr);
}

void test_array_free() 
{
  array intArr;
  int count = 5;
  unsigned long size = sizeof(int);

  assert(array_free(NULL) == -1);
  array_init(&intArr, 5, size);
  assert(array_free(&intArr) == 0);
}

void test_array_put() 
{
  array intArr;
  int count = 5;
  unsigned long size = sizeof(int);
  array_init(&intArr, count, size);

  for (int i = 0; i < count; i++) { 
    assert(array_put(NULL, i, &i) == -1); 
    assert(array_put(&intArr, i, NULL) == -1);
    assert(array_put(&intArr, i, &i) == 0);
    assert(*(((int *)intArr.data) + i) == i);
  }
  assert(array_put(&intArr, -1, &count) == -1);
  assert(array_put(&intArr, count, &count) == -1);
  array_free(&intArr);
}

void test_array_get() 
{
  array intArr;
  int count = 5;
  unsigned long size = sizeof(int);
  array_init(&intArr, count, size);

  for (int i = 0; i < count; i++) { 
    array_put(&intArr, i, &i);
    assert(*(int *)array_get(&intArr, i) == i);
  }

  assert(array_get(&intArr, -1) == NULL);
  assert(array_get(&intArr, count) == NULL);

  array_free(&intArr);
}
