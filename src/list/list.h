#ifndef LIST
#define LIST

#include "stdlib.h"
#include "string.h"

typedef struct list_node_t {
  void *data;
  struct list_node_t *next;
  unsigned int index;
} ListNode;

typedef struct {
  size_t dataSize;
  unsigned int length;
  ListNode *head;
} List;

int list_init(List *list, size_t size);
int list_free(List *list);

int list_add(List *list, void *data, size_t size);
int list_remove(List *list, int index);

ListNode *_list_get_last(ListNode *node);

#endif