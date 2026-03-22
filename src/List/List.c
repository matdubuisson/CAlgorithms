#include <stdlib.h>

#include "List/List.h"

// Who said switches are bad ?!

static List* create_concrete_list(List *list, uint32_t initial_length) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_create(list, initial_length);
        case LIST_LINKED:
            return LIST_LINKED_create(list);
        default: return NULL;
    }
}

extern List* LIST_create(ListType type, uint32_t initial_length, uint32_t data_size,
    int32_t (*comparator)(const void*, const void*)) {
    List *list = malloc(sizeof(List));
    if (list == NULL)
        return NULL;
    list->type = type;
    list->length = 0;
    list->data_size = data_size;
    list->comparator = comparator;
    List *concrete_list = create_concrete_list(list, initial_length);
    if (concrete_list == NULL)
        free(list);
    return concrete_list;
}

extern void LIST_destroy(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            LIST_ARRAY_destroy(list);
            break;
        case LIST_LINKED:
            LIST_LINKED_destroy(list);
            break;
        default: break;
    }
    free(list);
}

extern ListType LIST_get_type(const List *list) {
    return list->type;
}

extern uint32_t LIST_get_length(const List *list) {
    return list->length;
}

extern uint32_t LIST_get_data_size(const List *list) {
    return list->data_size;
}

extern uint8_t LIST_is_sorted(const List *list) {
    return list->flags & LIST_SORTED;
}

extern int8_t LIST_add_first(List *list, void *element) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_add_first(list, element);
        case LIST_LINKED:
            return LIST_LINKED_add_first(list, element);
        default: return -1;
    }
}

extern int8_t LIST_add_last(List *list, void *element) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_add_last(list, element);
        case LIST_LINKED:
            return LIST_LINKED_add_last(list, element);
        default: return -1;
    }
}

extern int8_t LIST_add(List *list, void *element) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_add(list, element);
        case LIST_LINKED:
            return LIST_LINKED_add(list, element);
        default: return -1;
    }
}

extern int8_t LIST_insert(List *list, void *element, uint32_t index) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_insert(list, element, index);
        case LIST_LINKED:
            return LIST_LINKED_insert(list, element, index);
        default: return -1;
    }
}

extern int8_t LIST_set(List *list, void *element, uint32_t index) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_set(list, element, index);
        case LIST_LINKED:
            return LIST_LINKED_set(list, element, index);
        default: return -1;
    }
}

extern void *LIST_get_first(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_get_first(list);
        case LIST_LINKED:
            return LIST_LINKED_get_first(list);
        default: return NULL;
    }
}

extern void *LIST_get_last(List * list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_get_last(list);
        case LIST_LINKED:
            return LIST_LINKED_get_last(list);
        default: return NULL;
    }
}

extern void *LIST_get(List *list, uint32_t index) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_get(list, index);
        case LIST_LINKED:
            return LIST_LINKED_get(list, index);
        default: return NULL;
    }
}

extern int8_t LIST_contains(List *list, void *element) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_contains(list, element);
        case LIST_LINKED:
            return LIST_LINKED_contains(list, element);
        default: return -1;
    }
}

extern uint32_t LIST_find(List *list, void *element) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_find(list, element);
        case LIST_LINKED:
            return LIST_LINKED_find(list, element);
        default: return -1;
    }
}

extern void *LIST_remove_first(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_remove_first(list);
        case LIST_LINKED:
            return LIST_LINKED_remove_first(list);
        default: return NULL;
    }
}

extern void *LIST_remove_last(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_remove_last(list);
        case LIST_LINKED:
            return LIST_LINKED_remove_last(list);
        default: return NULL;
    }
}

extern void *LIST_remove(List *list, uint32_t index) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_remove(list, index);
        case LIST_LINKED:
            return LIST_LINKED_remove(list, index);
        default: return NULL;
    }
}
extern int8_t LIST_clear(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_clear(list);
        case LIST_LINKED:
            return LIST_LINKED_clear(list);
        default: return -1;
    }
}

extern int8_t LIST_sort(List *list) {
    switch (list->type) {
        case LIST_ARRAY:
            return LIST_ARRAY_sort(list);
        case LIST_LINKED:
            return LIST_LINKED_sort(list);
        default: return -1;
    }
}