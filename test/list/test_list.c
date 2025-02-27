#include "test_list.h"

void test_list() {
  test_list_init();
  test_list_free();
}

void test_list_init() {

  List list;
  assert(list_init(NULL, sizeof(int)) < 0);
  assert(list_init(&list, 0) < 0);
  assert(!list_init(&list, sizeof(int)));
  if (list_free(&list) < 0) exit(1);
}

void test_list_free() {
  List list;
  if (list_init(&list, sizeof(int)) < 0) exit(1);
  assert(list_free(NULL) < 0);
  assert(!list_free(&list));
}
