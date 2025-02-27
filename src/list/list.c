#include "list.h"

int list_init(List *list, size_t size) {
  if (!list || !size) return -1;

  list->dataSize = size;
  list->head = NULL;
  list->length = 0;
  return 0;
}

int list_free(List *list) {
  if (!list) return -1;
  if (!list->head) return 0;

  ListNode *current = list->head, *last;

  while (current != NULL) { // TODO maybe a memory leak
    last = current;
    current = current->next;

    free(current->data);
    free(current);
  }

  if (last) {
    free(current->data);
    free(current);
  }

  list->head = NULL;

  return 0;
}