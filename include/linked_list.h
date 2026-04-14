#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "types.h"


struct node_t {
   struct node_t *next;
   void *data;
};

typedef struct {
    struct node *head;
    uint elementSize;
    uint count;
} linked_list;

int linked_list_init(linked_list *list, uint s);

void linked_list_free(linked_list *list);

void *linked_list_get(linked_list *list, uint i);

void linked_list_set(linked_list *list, void *data, uint i);

void linked_list_insert(linked_list *list, void *data, uint i);

void linked_list_remove(linked_list *list, uint i);

#endif
