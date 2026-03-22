#include <stdlib.h>
#include <string.h>

#include "list/list.h"
#include "list/linked_list.h"

static linked_list_t *get_concrete_data(list_t *list) {
    return &list->concrete.linked_list;
}

static linked_list_node_t *create_new_node(list_t *list, void *element) {
    linked_list_node_t *newNode = malloc(sizeof(linked_list_node_t));
    if (newNode != NULL) {
        newNode->element = element;
        newNode->next = NULL;
    }
    return newNode;
}

extern list_t* linked_list_create(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list->head = NULL;
    linked_list->tail = NULL;
    return list;
}

extern void linked_list_destroy(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *current = linked_list->head, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    linked_list->head = NULL;
}

extern int8_t linked_list_add_first(list_t *list, void *element) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (linked_list->head == NULL)
        linked_list->head = linked_list->tail = newNode;
    else {
        newNode->next = linked_list->head;
        linked_list->head = newNode;
    }
    list->length++;
    return 0;
}

extern int8_t linked_list_add_last(list_t *list, void *element) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (linked_list->tail == NULL)
        linked_list->head = linked_list->tail = newNode;
    else {
        linked_list->tail->next = newNode;
        linked_list->tail = newNode;
    }
    list->length++;
    return 0;
}

extern int8_t linked_list_add(list_t *list, void *element) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (linked_list->head == NULL)
        linked_list->head = linked_list->tail = newNode;
    else {
        linked_list_node_t *previous = NULL, *current = linked_list->head;
        while (current != NULL
            && list->comparator(element, current->element) > 0) {
            previous = current;
            current = current->next;
        }
        newNode->next = current;
        if (previous == NULL)
            linked_list->head = newNode;
        else {
            if (current == NULL)
                linked_list->tail = newNode;
            previous->next = newNode;
        }
    }
    list->length++;
    return 0;
}

extern int8_t linked_list_insert(list_t *list, void *element, uint32_t index) {
    linked_list_t *linked_list = get_concrete_data(list);
    if (index == 0 || index == list->length) {
        linked_list_node_t *newNode = create_new_node(list, element);
        if (newNode == NULL)
            return -1;
        else if (index == 0) {
            newNode->next = linked_list->head;
            linked_list->head = newNode;
        } else {
            linked_list->tail->next = newNode;
            linked_list->tail = newNode;
        }
    } else if (index < list->length) {
        linked_list_node_t *previous = linked_list->head, *current = previous->next;
        for (uint32_t i = 1; i < list->length && current != NULL; i++, previous = current, current = current->next) {
            if (i == index) {
                linked_list_node_t *newNode = create_new_node(list, element);
                if (newNode == NULL)
                    return -1;
                previous->next = newNode;
                newNode->next = current;
                break;
            }
        }
    } else return -1;
    list->length++;
    return 0;
}

extern int8_t linked_list_set(list_t *list, void *element, uint32_t index) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *current = linked_list->head;
    for (uint32_t i = 0; i < list->length && current != NULL; i++, current = current->next) {
        if (i == index) {
            current->element = element;
            return 0;
        }
    }
    return -1;
}

extern uint32_t linked_list_get_length(const list_t *list) {
    return list->length;
}

extern void *linked_list_get_first(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    return linked_list->head == NULL ? NULL : linked_list->head->element;
}

extern void *linked_list_get_last(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    return linked_list->tail == NULL ? NULL : linked_list->tail->element;
}

extern void *linked_list_get(list_t *list, uint32_t index) {
    if (index >= list->length) return NULL;
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *current = linked_list->head;
    uint32_t i = 0;
    while (i < index && current != NULL) {
        i++;
        current = current->next;
    }
    if (i != index)
        return NULL;
    else
        return current->element;
}

extern int8_t linked_list_contains(list_t *list, void *element) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *current = linked_list->head;
    while (current != NULL) {
        if (list->comparator(element, current->element) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

extern uint32_t linked_list_find(list_t *list, void *element) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *current = linked_list->head;
    uint32_t index = 0;
    while (current != NULL) {
        if (list->comparator(current->element, element) == 0)
            return index;
        current = current->next;
        index++;
    }
    return UINT32_MAX;
}

extern void *linked_list_remove_first(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    if (linked_list->head == NULL)
        return NULL;
    linked_list_node_t *old_head = linked_list->head;
    void *head_element = old_head->element;
    if (linked_list->head == linked_list->tail)
        linked_list->head = linked_list->tail = NULL;
    else
        linked_list->head = old_head->next;
    free(old_head);
    list->length--;
    return head_element;
}

extern void *linked_list_remove_last(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    if (linked_list->head == NULL)
        return NULL;
    linked_list_node_t *old_tail = linked_list->tail;
    void *tail_element = old_tail->element;
    if (linked_list->head == linked_list->tail)
        linked_list->head = linked_list->tail = NULL;
    else {
        linked_list_node_t *current = linked_list->head;
        while (current->next != old_tail)
            current = current->next;
        linked_list->tail = current;
    }
    free(old_tail);
    list->length--;
    return tail_element;
}

extern void *linked_list_remove(list_t *list, uint32_t index) {
    if (list->length == 0)
        return NULL;
    else if (index == 0)
        return linked_list_remove_first(list);
    else if (index == list->length - 1)
        return linked_list_remove_last(list);
    else {
        linked_list_t *linked_list = get_concrete_data(list);
        linked_list_node_t *previous = linked_list->head, *current = previous->next;
        uint32_t i = 0;
        while (current != linked_list->tail) {
            if (i == index - 1) {
                void *removed_element = current->element;
                previous->next = current->next;
                free(current);
                list->length--;
                return removed_element;
            }
            previous = current;
            current = current->next;
            i++;
        }
        return NULL;
    }
}

extern int8_t linked_list_clear(list_t *list) {
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *previous, *current = linked_list->head;
    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
    linked_list->head = linked_list->tail = NULL;
    list->length = 0;
    return 0;
}

extern int8_t linked_list_sort(list_t *list) {
    // Values are easier to exchange than nodes
    linked_list_t *linked_list = get_concrete_data(list);
    linked_list_node_t *minimal = linked_list->head, *current;
    void *tmp;
    while (minimal != NULL) {
        current = minimal->next;
        while (current != NULL) {
            if (list->comparator(current->element, minimal->element) < 0) {
                tmp = minimal->element;
                minimal->element = current->element;
                current->element = tmp;
            }
            current = current->next;
        }
        minimal = minimal->next;
    }
    return 0;
}
