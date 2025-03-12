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

  ListNode *current = list->head, *last = NULL;

  while (current) {
    last = current;
    current = current->next;

    free(last->data);
    free(last);
  }

  if (current) {
    free(current->data);
    free(current);
  }

  list->head = NULL;

  return 0;
}

int list_add(List *list, void *data, size_t size) 
{
  if (!list || !data || size != list->dataSize) return -1;

  ListNode *last = _list_get_last(list->head);
  if (!last) { 
    if (!(list->head = malloc(sizeof(ListNode)))) exit(1);
    last = list->head;
  }
  else {
    if (!(last->next = malloc(sizeof(ListNode)))) exit(1);
    last = last->next;
  }

  last->index = list->length++;
  last->next = NULL;
  if (!(last->data = malloc(sizeof(size)))) exit(1);
  if (!memcpy(last->data, data, size)) exit(1);
  return 0;
}

int list_remove(List *list, int index) 
{
  if (!list || index < 0 || index >= list->length) return -1;

  ListNode *node = list->head, *prev = NULL;
  while (node->index != index) {
    prev = node;
    node = node->next; 
  }

  if (prev) prev->next = node->next;
  else { 
    list->head = node->next;
    prev = list->head;
    if (prev) prev->index--;
  }

  free(node->data);
  free(node);
  list->length--;
  if (!list->head) return 0;
  // Update indices
  while ((prev = prev->next)) prev->index--;
  return 0;
}

void *list_get(List *list, int index) {
  if (!list || index < 0 || index >= list->length) return NULL;

  ListNode *current = list->head;
  while (current->index != index) current = current->next;

  return current->data;
}

ListNode *_list_get_last(ListNode *node) {
  if (!node) return NULL;

  while (node->next) node = node->next;
  return node;
}