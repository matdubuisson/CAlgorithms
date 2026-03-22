#ifndef __ARRAY_LIST__LIBRARY__
#define __ARRAY_LIST__LIBRARY__

#include "list/list.h"

typedef struct list list_t;

typedef struct array_list {
    void **array;
    uint32_t start, stop;
    uint32_t array_length;
} array_list_t;

list_t* array_list_create(list_t *list, uint32_t initial_length);
void array_list_destroy(list_t *list);

int8_t array_list_add_last(list_t *list, void *element);
int8_t array_list_add_first(list_t *list, void *element);
int8_t array_list_add(list_t *list, void *element);

int8_t array_list_insert(list_t *list, void *element, uint32_t index);

int8_t array_list_set(list_t *list, void *element, uint32_t index);

void *array_list_get_first(list_t *list);
void *array_list_get_last(list_t * list);
void *array_list_get(list_t *list, uint32_t index);

int8_t array_list_contains(list_t *list, void *element);
uint32_t array_list_find(list_t *list, void *element);

void *array_list_remove_first(list_t *list);
void *array_list_remove_last(list_t *list);
void *array_list_remove(list_t *list, uint32_t index);

int8_t array_list_clear(list_t *list);
int8_t array_list_sort(list_t *list);

#endif