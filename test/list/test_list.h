#ifndef TEST_LIST
#define TEST_LIST

#include "stdio.h"
#include "assert.h"
#include "list.h"

void test_list();

void test_list_init();
void test_list_free();

void test_list_add();
void test_list_remove();

void test_list_get();

void check_node(ListNode *node, int expectedIndex, int expectedData);

#endif