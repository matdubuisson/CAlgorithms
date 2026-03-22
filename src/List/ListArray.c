#include <stdlib.h>
#include <string.h>

#include "List/List.h"

static ListArray *get_concrete_data(List *list) {
    return &list->concrete.list_array;
}

extern List* LIST_ARRAY_create(List *list, uint32_t initial_length) {
    ListArray *list_array = get_concrete_data(list);
    if (initial_length > 0) {
        list_array->array = malloc(list->data_size * initial_length);
        if (list_array->array == NULL)
            return NULL;
    }
    list_array->array_length = initial_length;
    list_array->start = 0;
    list_array->stop = initial_length;
    return list;
}

extern void LIST_ARRAY_destroy(List *list) {
    ListArray *list_array = get_concrete_data(list);
    free(list_array->array);
}

static inline int8_t check_array(List *list, ListArray *list_array) {
    if (list->length == list_array->array_length) {
        uint32_t new_length = list_array->array_length * 2;
        void *new_array = realloc(list_array->array, new_length);
        if (new_array == NULL)
            return -1;
        list_array->array = new_array;
        list_array->array_length = new_length;
    } else if (list->length < list_array->array_length / 4) {
        uint32_t new_length = list_array->array_length / 2;
        void *new_array = realloc(list_array->array, new_length);
        if (new_array == NULL)
            return -1;
        list_array->array = new_array;
        list_array->array_length = new_length;
    }
    return 0;
}

extern int8_t LIST_ARRAY_add_first(List *list, void *element) {
    ListArray *list_array = get_concrete_data(list);
    if (check_array(list, list_array) == -1)
        return -1;
    memcpy(&list_array->array[list->length], element, list->data_size);
    list->length++;
    return 0;
}

extern int8_t LIST_ARRAY_add_last(List *list, void *element) {
    ListArray *list_array = get_concrete_data(list);
    if (check_array(list, list_array) == -1)
        return -1;
    memcpy(&list_array->array[list->length], element, list->data_size);
    list->length++;
    return 0;
}

extern int8_t LIST_ARRAY_add(List *list, void *element) {
    ListArray *list_array = get_concrete_data(list);
    if (check_array(list, list_array) == -1)
        return -1;
    return 0;
}

extern int8_t LIST_ARRAY_insert(List *list, void *element, uint32_t index) {
    return 0;
}

extern int8_t LIST_ARRAY_set(List *list, void *element, uint32_t index) {
    return 0;
}

extern uint32_t LIST_ARRAY_get_length(const List *list) {
    return 0;
}

extern void *LIST_ARRAY_get_first(List *list) {
    return NULL;
}

extern void *LIST_ARRAY_get_last(List *list) {
    return NULL;
}

extern void *LIST_ARRAY_get(List *list, uint32_t index) {
    return NULL;
}

extern int8_t LIST_ARRAY_contains(List *list, void *element) {
    ListArray *list_array = get_concrete_data(list);
    if (check_array(list, list_array) == -1)
        return -1;
    for (uint32_t i = 0; i < list->length; i++) {
        if (list->comparator(list_array->array[i], element) == 0)
            return 1;
    }
    return 0;
}

extern uint32_t LIST_ARRAY_find(List *list, void *element) {
    return UINT32_MAX;
}

extern void *LIST_ARRAY_remove_first(List *list) {
    return 0;
}

extern void *LIST_ARRAY_remove_last(List *list) {
    return 0;
}

extern void *LIST_ARRAY_remove(List *list, uint32_t index) {
    return 0;
}

extern int8_t LIST_ARRAY_clear(List *list) {
    return 0;    
}

extern int8_t LIST_ARRAY_sort(List *list) {
    return 0;    
}
