#include <stdlib.h>

#include "list/list.h"

// Who said switches are bad ?!

static list_t* create_concrete_list(list_t *list, uint32_t initial_length) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_create(list, initial_length);
        case LINKED_LIST:
            return linked_list_create(list);
        default: return NULL;
    }
}

extern list_t* list_create(list_type_t type, uint32_t initial_length, uint32_t data_size,
    int32_t (*comparator)(const void*, const void*)) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;
    list->type = type;
    list->length = 0;
    list->data_size = data_size;
    list->comparator = comparator;
    list_t *concrete_list = create_concrete_list(list, initial_length);
    if (concrete_list == NULL)
        free(list);
    return concrete_list;
}

extern void list_destroy(list_t *list) {
    switch (list->type) {
        case ARRAY_LIST:
            array_list_destroy(list);
            break;
        case LINKED_LIST:
            linked_list_destroy(list);
            break;
        default: break;
    }
    free(list);
}

extern list_type_t list_get_type(const list_t *list) {
    return list->type;
}

extern uint32_t list_get_length(const list_t *list) {
    return list->length;
}

extern uint32_t list_get_data_size(const list_t *list) {
    return list->data_size;
}

extern uint8_t list_is_sorted(const list_t *list) {
    return list->flags & list_SORTED;
}

extern int8_t list_add_first(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_add_first(list, element);
        case LINKED_LIST:
            return linked_list_add_first(list, element);
        default: return -1;
    }
}

extern int8_t list_add_last(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_add_last(list, element);
        case LINKED_LIST:
            return linked_list_add_last(list, element);
        default: return -1;
    }
}

extern int8_t list_add(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_add(list, element);
        case LINKED_LIST:
            return linked_list_add(list, element);
        default: return -1;
    }
}

extern int8_t list_insert(list_t *list, void *element, uint32_t index) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_insert(list, element, index);
        case LINKED_LIST:
            return linked_list_insert(list, element, index);
        default: return -1;
    }
}

extern int8_t list_set(list_t *list, void *element, uint32_t index) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_set(list, element, index);
        case LINKED_LIST:
            return linked_list_set(list, element, index);
        default: return -1;
    }
}

extern void *list_get_first(list_t *list) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_get_first(list);
        case LINKED_LIST:
            return linked_list_get_first(list);
        default: return NULL;
    }
}

extern void *list_get_last(list_t * list) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_get_last(list);
        case LINKED_LIST:
            return linked_list_get_last(list);
        default: return NULL;
    }
}

extern void *list_get(list_t *list, uint32_t index) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_get(list, index);
        case LINKED_LIST:
            return linked_list_get(list, index);
        default: return NULL;
    }
}

extern int8_t list_contains(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_contains(list, element);
        case LINKED_LIST:
            return linked_list_contains(list, element);
        default: return -1;
    }
}

extern uint32_t list_find(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_find(list, element);
        case LINKED_LIST:
            return linked_list_find(list, element);
        default: return -1;
    }
}

extern void *list_remove_first(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_remove_first(list, element);
        case LINKED_LIST:
            return linked_list_remove_first(list, element);
        default: return NULL;
    }
}

extern void *list_remove_last(list_t *list, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_remove_last(list, element);
        case LINKED_LIST:
            return linked_list_remove_last(list, element);
        default: return NULL;
    }
}

extern void *list_remove(list_t *list, uint32_t index, void *element) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_remove(list, index, element);
        case LINKED_LIST:
            return linked_list_remove(list, index, element);
        default: return NULL;
    }
}
extern int8_t list_clear(list_t *list) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_clear(list);
        case LINKED_LIST:
            return linked_list_clear(list);
        default: return -1;
    }
}

extern int8_t list_sort(list_t *list) {
    switch (list->type) {
        case ARRAY_LIST:
            return array_list_sort(list);
        case LINKED_LIST:
            return linked_list_sort(list);
        default: return -1;
    }
}