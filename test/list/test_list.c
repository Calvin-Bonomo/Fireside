#include "test_list.h"

void test_list() {
  test_list_init();
  test_list_free();
  test_list_add();
  test_list_remove();
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

void test_list_add() {
  List list;
  int val = 6;
  if (list_init(&list, sizeof(int)) < 0) exit(1);

  // Check for invalid input
  assert(list_add(NULL, (void *)&val, sizeof(int)) < 0);
  assert(list_add(&list, NULL, sizeof(int)) < 0);
  assert(list_add(&list, &val, 0) < 0);
  assert(list_add(&list, &val, 27) < 0);
  assert(!list.length);
  assert(!list.head);

  // Check valid input
  assert(!list_add(&list, (void *)&val, sizeof(int)));
  assert(list.length == 1);
  check_node(list.head, 0, val);
  assert(!list_add(&list, (void *)&val, sizeof(int)));
  check_node(list.head->next, 1, val);
  if (list_free(&list) < 0) exit(1);
}

void test_list_remove() {
  List list;
  int val = 6;
  if (list_init(&list, sizeof(int)) < 0) exit(1);
  if (list_add(&list, &val, sizeof(int)) < 0) exit(1);
  if (list_add(&list, &val, sizeof(int)) < 0) exit(1);

  // Fail test cases
  assert(list_remove(&list, -1) < 0);
  assert(list_remove(&list, 2) < 0);
  assert(list_remove(NULL, 1) < 0);
  // Test pass cases
  assert(!list_remove(&list, 1));
  assert(!list_remove(&list, 0));
  assert(!list.length);

  if (list_free(&list) < 0) exit(1);
}

void check_node(ListNode *node, int expectedIndex, int expectedData) {
  if (!node) exit(1);
  assert(node->index == expectedIndex);
  assert(*(int *)node->data == expectedData);
}