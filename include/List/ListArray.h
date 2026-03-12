#ifndef __LIST_ARRAY__LIBRARY__
#define __LIST_ARRAY__LIBRARY__

typedef struct List List;

typedef struct ListArray {
    void **array;
    uint32_t start, stop;
    uint32_t array_length;
} ListArray;

List* LIST_ARRAY_create(List *list, uint32_t initial_length);
void LIST_ARRAY_destroy(List *list);

int8_t LIST_ARRAY_add_last(List *list, void *element);
int8_t LIST_ARRAY_add_first(List *list, void *element);
int8_t LIST_ARRAY_add(List *list, void *element);

int8_t LIST_ARRAY_insert(List *list, void *element, uint32_t index);

int8_t LIST_ARRAY_set(List *list, void *element, uint32_t index);

void *LIST_ARRAY_get_first(List *list);
void *LIST_ARRAY_get_last(List * list);
void *LIST_ARRAY_get(List *list, uint32_t index);

int8_t LIST_ARRAY_contains(List *list, void *element);
uint32_t LIST_ARRAY_find(List *list, void *element);

void *LIST_ARRAY_remove_first(List *list);
void *LIST_ARRAY_remove_last(List *list);
void *LIST_ARRAY_remove(List *list, uint32_t index);

int8_t LIST_ARRAY_clear(List *list);
int8_t LIST_ARRAY_sort(List *list);

#endif