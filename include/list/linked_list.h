#ifndef __LINKED_LIST__LIBRARY__
#define __LINKED_LIST__LIBRARY__

#include "list/list.h"

typedef struct list list_t;

typedef struct linked_list_node {
    void *element;
    struct linked_list_node *next;
} linked_list_node_t;

typedef struct linked_list {
    linked_list_node_t *head, *tail;
} linked_list_t;

list_t* linked_list_create(list_t *list);
void linked_list_destroy(list_t *list);

int8_t linked_list_add_last(list_t *list, void *element);
int8_t linked_list_add_first(list_t *list, void *element);
int8_t linked_list_add(list_t *list, void *element);

int8_t linked_list_insert(list_t *list, void *element, uint32_t index);

int8_t linked_list_set(list_t *list, void *element, uint32_t index);

void *linked_list_get_first(list_t *list);
void *linked_list_get_last(list_t * list);
void *linked_list_get(list_t *list, uint32_t index);

int8_t linked_list_contains(list_t *list, void *element);
uint32_t linked_list_find(list_t *list, void *element);

void *linked_list_remove_first(list_t *list);
void *linked_list_remove_last(list_t *list);
void *linked_list_remove(list_t *list, uint32_t index);

int8_t linked_list_clear(list_t *list);
int8_t linked_list_sort(list_t *list);

#endif