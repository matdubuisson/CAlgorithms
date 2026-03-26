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

static void insert_and_shift(const list_t *list, const array_list_t *array_list,
    const void *element, const uint32_t index) {
    for (uint32_t i = list->length, k = list->length * list->data_size;
        i > index; --i, k -= list->data_size) {
        memcpy(&array_list->array[k], &array_list->array[k - list->data_size], list->data_size);
    }
    memcpy(&array_list->array[index * list->data_size], element, list->data_size);
}

static void shift_back(const list_t *list, const array_list_t *array_list,
    const uint32_t index) {
    for (uint32_t i = index, k = index * list->data_size;
        i < list->length - 1; ++i, k += list->data_size) {
        memcpy(&array_list->array[k], &array_list->array[k + list->data_size], list->data_size);
    }
}

extern int8_t array_list_add_first(list_t *list, void *element) {
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    insert_and_shift(list, array_list, element, 0);
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
    for (uint32_t i = 0, k = 0; i < list->length; i++, k += list->data_size) {
        if (list->comparator(element, &array_list->array[k]) <= 0) {
            insert_and_shift(list, array_list, element, i);
            list->length++;
            return 0;
        }
    }
    memcpy(&array_list->array[list->length * list->data_size], element, list->data_size);
    list->length++;
    return 0;
}

extern int8_t array_list_insert(list_t *list, void *element, uint32_t index) {
    if (index > list->length) // Index can be == list->length for an insertion
        return -1;
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    insert_and_shift(list, array_list, element, index);
    list->length++;
    return 0;
}

extern int8_t array_list_set(list_t *list, void *element, uint32_t index) {
    if (index >= list->length)
        return -1;
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return -1;
    memcpy(&array_list->array[index * list->data_size], element, list->data_size);
    return 0;
}

extern void *array_list_get_first(list_t *list) {
    if (list->length == 0)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    return &array_list->array[0];
}

extern void *array_list_get_last(list_t *list) {
    if (list->length == 0)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    return &array_list->array[(list->length - 1) * list->data_size];
}

extern void *array_list_get(list_t *list, uint32_t index) {
    if (list->length == 0)
        return NULL;
    else if (index >= list->length)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    return &array_list->array[index * list->data_size];
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
    array_list_t *array_list = get_concrete_data(list);
    for (uint32_t i = 0, k = 0; i < list->length; i++, k += list->data_size) {
        if (!memcmp(&array_list->array[k], element, list->data_size)) {
            return i;
        }
    }
    return UINT32_MAX;
}

extern void *array_list_remove_first(list_t *list, void *element) {
    if (list->length == 0)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return NULL;
    memcpy(element, &array_list->array[0], list->data_size);
    shift_back(list, array_list, 0);
    list->length--;
    return element;
}

extern void *array_list_remove_last(list_t *list, void *element) {
    if (list->length == 0)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return NULL;
    memcpy(element, &array_list->array[(list->length - 1) * list->data_size], list->data_size);
    list->length--;
    return element;
}

extern void *array_list_remove(list_t *list, uint32_t index, void *element) {
    if (list->length == 0)
        return NULL;
    else if (index >= list->length)
        return NULL;
    array_list_t *array_list = get_concrete_data(list);
    if (check_array(list, array_list) == -1)
        return NULL;
    memcpy(element, &array_list->array[index * list->data_size], list->data_size);
    shift_back(list, array_list, index);
    list->length--;
    return element;
}

extern int8_t array_list_clear(list_t *list) {
    array_list_t *array_list = get_concrete_data(list);
    free(array_list->array);
    array_list->array = malloc(list->data_size);
    if (array_list->array == NULL) {
        array_list->array_length = 0;
        return -1;
    }
    array_list->array_length = 1;
    list->length = 0;
    return 0;
}

static int8_t array_list_merge_sort_aux(list_t *list, array_list_t *array_list, uint32_t i, uint32_t j) {
    if (i >= j)
        return 0;
    uint32_t m = (i + j) / 2;
    array_list_merge_sort_aux(list, array_list, i, m);
    array_list_merge_sort_aux(list, array_list, m + 1, j);

    uint32_t left_length = m - i + 1, right_length = j - m;
    uint32_t k = i;
    uint8_t buffer[list->data_size * (j - i + 1)];
    while (i < left_length && j < right_length) {
        if (list->comparator(
            &array_list->array[i * list->data_size],
            &array_list->array[j * list->data_size]
            ) <= 0) {
            memcpy(&buffer[k * list->data_size], &array_list->array[i * list->data_size], list->data_size);
            i++;
        } else {
            memcpy(&buffer[k * list->data_size], &array_list->array[j * list->data_size], list->data_size);
            j++;
        }
    }

    for (; i < left_length; i++)
        memcpy(&buffer[k * list->data_size], &array_list->array[i * list->data_size], list->data_size);

    for (; j < right_length; j++)
        memcpy(&buffer[k * list->data_size], &array_list->array[j * list->data_size], list->data_size);
    
    for (k = 0; k < (j - i + 1); k++)
        memcpy(&array_list->array[(i + k) * list->data_size], &buffer[k * list->data_size], list->data_size);
}

extern int8_t array_list_merge_sort(list_t *list) {
    if (list->length < 2)
        return 0;
    array_list_t *array_list = get_concrete_data(list);
    return array_list_merge_sort_aux(list, array_list, 0, list->length - 1);
}

extern int8_t array_list_sort(list_t *list) {
    return array_list_merge_sort(list);
}
