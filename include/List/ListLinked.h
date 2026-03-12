#ifndef __LIST_LINKED__LIBRARY__
#define __LIST_LINKED__LIBRARY__

typedef struct List List;

typedef struct ListLinkedNode {
    void *element;
    struct ListLinkedNode *next;
} ListLinkedNode;

typedef struct ListLinked {
    ListLinkedNode *head, *tail;
} ListLinked;

List* LIST_LINKED_create(List *list);
void LIST_LINKED_destroy(List *list);

int8_t LIST_LINKED_add_last(List *list, void *element);
int8_t LIST_LINKED_add_first(List *list, void *element);
int8_t LIST_LINKED_add(List *list, void *element);

int8_t LIST_LINKED_insert(List *list, void *element, uint32_t index);

int8_t LIST_LINKED_set(List *list, void *element, uint32_t index);

void *LIST_LINKED_get_first(List *list);
void *LIST_LINKED_get_last(List * list);
void *LIST_LINKED_get(List *list, uint32_t index);

int8_t LIST_LINKED_contains(List *list, void *element);
uint32_t LIST_LINKED_find(List *list, void *element);

void *LIST_LINKED_remove_first(List *list);
void *LIST_LINKED_remove_last(List *list);
void *LIST_LINKED_remove(List *list, uint32_t index);

int8_t LIST_LINKED_clear(List *list);
int8_t LIST_LINKED_sort(List *list);

#endif