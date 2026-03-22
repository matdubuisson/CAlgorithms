#include <stdlib.h>
#include <string.h>

#include "List/List.h"
#include "List/ListLinked.h"

static ListLinked *get_concrete_data(List *list) {
    return &list->concrete.list_linked;
}

static ListLinkedNode *create_new_node(List *list, void *element) {
    ListLinkedNode *newNode = malloc(list->data_size);
    if (newNode != NULL) {
        newNode->element = element;
        newNode->next = NULL;
    }
    return newNode;
}

extern List* LIST_LINKED_create(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    list_linked->head = NULL;
    list_linked->tail = NULL;
    return list;
}

extern void LIST_LINKED_destroy(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *current = list_linked->head, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list_linked->head = NULL;
}

extern int8_t LIST_LINKED_add_first(List *list, void *element) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (list_linked->head == NULL)
        list_linked->head = list_linked->tail = newNode;
    else {
        newNode->next = list_linked->head;
        list_linked->head = newNode;
    }
    list->length++;
    return 0;
}

extern int8_t LIST_LINKED_add_last(List *list, void *element) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (list_linked->tail == NULL)
        list_linked->head = list_linked->tail = newNode;
    else {
        list_linked->tail->next = newNode;
        list_linked->tail = newNode;
    }
    list->length++;
    return 0;
}

extern int8_t LIST_LINKED_add(List *list, void *element) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *newNode = create_new_node(list, element);
    if (newNode == NULL)
        return -1;
    else if (list_linked->head == NULL)
        list_linked->head = list_linked->tail = newNode;
    else {
        ListLinkedNode *previous = NULL, *current = list_linked->head;
        while (current != NULL
            && list->comparator(element, current->element) > 0) {
            previous = current;
            current = current->next;
        }
        newNode->next = current;
        if (previous == NULL)
            list_linked->head = newNode;
        else {
            if (current == NULL)
                list_linked->tail = newNode;
            previous->next = newNode;
        }
    }
    list->length++;
    return 0;
}

extern int8_t LIST_LINKED_insert(List *list, void *element, uint32_t index) {
    ListLinked *list_linked = get_concrete_data(list);
    if (index == 0 || index == list->length) {
        ListLinkedNode *newNode = create_new_node(list, element);
        if (newNode == NULL)
            return -1;
        else if (index == 0) {
            newNode->next = list_linked->head;
            list_linked->head = newNode;
        } else {
            list_linked->tail->next = newNode;
            list_linked->tail = newNode;
        }
    } else if (index < list->length) {
        ListLinkedNode *previous = list_linked->head, *current = previous->next;
        for (uint32_t i = 1; i < list->length && current != NULL; i++, previous = current, current = current->next) {
            if (i == index) {
                ListLinkedNode *newNode = create_new_node(list, element);
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

extern int8_t LIST_LINKED_set(List *list, void *element, uint32_t index) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *current = list_linked->head;
    for (uint32_t i = 0; i < list->length && current != NULL; i++, current = current->next) {
        if (i == index) {
            current->element = element;
            return 0;
        }
    }
    return -1;
}

extern uint32_t LIST_LINKED_get_length(const List *list) {
    return list->length;
}

extern void *LIST_LINKED_get_first(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    return list_linked->head == NULL ? NULL : list_linked->head->element;
}

extern void *LIST_LINKED_get_last(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    return list_linked->tail == NULL ? NULL : list_linked->tail->element;
}

extern void *LIST_LINKED_get(List *list, uint32_t index) {
    if (index >= list->length) return NULL;
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *current = list_linked->head;
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

extern int8_t LIST_LINKED_contains(List *list, void *element) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *current = list_linked->head;
    while (current != NULL) {
        if (list->comparator(element, current->element) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

extern uint32_t LIST_LINKED_find(List *list, void *element) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *current = list_linked->head;
    uint32_t index = 0;
    while (current != NULL) {
        if (list->comparator(current->element, element) == 0)
            return index;
        current = current->next;
        index++;
    }
    return UINT32_MAX;
}

extern void *LIST_LINKED_remove_first(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    if (list_linked->head == NULL)
        return NULL;
    ListLinkedNode *old_head = list_linked->head;
    void *head_element = old_head->element;
    if (list_linked->head == list_linked->tail)
        list_linked->head = list_linked->tail = NULL;
    else
        list_linked->head = old_head->next;
    free(old_head);
    list->length--;
    return head_element;
}

extern void *LIST_LINKED_remove_last(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    if (list_linked->head == NULL)
        return NULL;
    ListLinkedNode *old_tail = list_linked->tail;
    void *tail_element = old_tail->element;
    if (list_linked->head == list_linked->tail)
        list_linked->head = list_linked->tail = NULL;
    else {
        ListLinkedNode *current = list_linked->head;
        while (current->next != old_tail)
            current = current->next;
        list_linked->tail = current;
    }
    free(old_tail);
    list->length--;
    return tail_element;
}

extern void *LIST_LINKED_remove(List *list, uint32_t index) {
    if (list->length == 0)
        return NULL;
    else if (index == 0)
        return LIST_LINKED_remove_first(list);
    else if (index == list->length - 1)
        return LIST_LINKED_remove_last(list);
    else {
        ListLinked *list_linked = get_concrete_data(list);
        ListLinkedNode *previous = list_linked->head, *current = previous->next;
        uint32_t i = 0;
        while (current != list_linked->tail) {
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

extern int8_t LIST_LINKED_clear(List *list) {
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *previous, *current = list_linked->head;
    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
    list_linked->head = list_linked->tail = NULL;
    list->length = 0;
    return 0;
}

extern int8_t LIST_LINKED_sort(List *list) {
    // Values are easier to exchange than nodes
    ListLinked *list_linked = get_concrete_data(list);
    ListLinkedNode *minimal = list_linked->head, *current;
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
