#ifndef LIST
#define LIST

#include "stdlib.h"

typedef struct list_node_t {
  void *data;
  struct list_node_t *next;
} ListNode;

typedef struct {
  size_t dataSize;
  unsigned int length;
  ListNode *head;
} List;

int list_init(List *list, size_t size);
int list_free(List *list);

#endif