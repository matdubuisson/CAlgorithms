#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list/list.h"

static array_list_t *get_concrete_data(list_t *list) {
    return &list->concrete.array_list;
}

extern list_t* array_list_create(list_t *list, uint32_t initial_length) {
    array_list_t *array_list = get_concrete_data(list);
    if (initial_length > 0) {
        array_list->array = malloc(list->data_size * initial_length);
        if (array_list->array == NULL)
            return NULL;
    } else array_list->array = NULL;
    array_list->array_length = initial_length;
    array_list->start = 0;
    array_list->stop = initial_length;
    return list;
}

extern void array_list_destroy(list_t *list) {
    array_list_t *array_list = get_concrete_data(list);
    free(array_list->array);
}

static inline int8_t check_array(list_t *list, array_list_t *array_list) {
    uint32_t new_length;
    if (list->length == array_list->array_length)
        new_length = array_list->array_length * 2;
    else if (list->length < array_list->array_length / 4)
        new_length = array_list->array_length / 2;
    else return 0;
    void *new_array = realloc(array_list->array, list->data_size * new_length);
    if (new_array == NULL)
        return -1;
    array_list->array = new_array;
    array_list->array_length = new_length;
    return 0;
}

extern int8_t array_list_add_first(list_t *list, void *element) {
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    for (uint32_t i = list->length; i > 1; i--)
        memcpy(&array_list->array[i], &array_list->array[i - 1], list->data_size);
    memcpy(&array_list->array[0], element, list->data_size);
    list->length++;
    return 0;
}

extern int8_t array_list_add_last(list_t *list, void *element) {
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    memcpy(&array_list->array[list->length * list->data_size], element, list->data_size);
    list->length++;
    return 0;
}

extern int8_t array_list_add(list_t *list, void *element) {
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    return 0;
}

extern int8_t array_list_insert(list_t *list, void *element, uint32_t index) {
    return 0;
}

extern int8_t array_list_set(list_t *list, void *element, uint32_t index) {
    return 0;
}

extern uint32_t array_list_get_length(const list_t *list) {
    return 0;
}

extern void *array_list_get_first(list_t *list) {
    return NULL;
}

extern void *array_list_get_last(list_t *list) {
    return NULL;
}

extern void *array_list_get(list_t *list, uint32_t index) {
    return NULL;
}

extern int8_t array_list_contains(list_t *list, void *element) {
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    for (uint32_t i = 0; i < list->length; i++) {
        if (list->comparator(&array_list->array[i * list->data_size], element) == 0)
            return 1;
    }
    return 0;
}

extern uint32_t array_list_find(list_t *list, void *element) {
    return UINT32_MAX;
}

extern void *array_list_remove_first(list_t *list, void *element) {
    return 0;
}

extern void *array_list_remove_last(list_t *list, void *element) {
    return 0;
}

extern void *array_list_remove(list_t *list, uint32_t index, void *element) {
    return 0;
}

extern int8_t array_list_clear(list_t *list) {
    return 0;    
}

extern int8_t array_list_sort(list_t *list) {
    return 0;    
}
