#ifndef __LIST__LIBRARY__
#define __LIST__LIBRARY__

#include <stdint.h>
#include <stddef.h>

typedef enum {
    ARRAY_LIST,
    LINKED_LIST,
    NOT_IMPLEMENTED_LIST
} list_type_t;

typedef enum {
    list_SORTED = 1
} list_flag_t;

#include "list/array_list.h"
#include "list/linked_list.h"

typedef union concrete_list {
    array_list_t array_list;
    linked_list_t linked_list;
} concrete_list_t;

typedef struct list {
    list_type_t type;

    uint32_t length;
    uint32_t data_size;
    uint8_t flags;

    int32_t (*comparator)(const void*, const void*);

    concrete_list_t concrete;
} list_t;

// Allocation Management

/**
 * @brief Create a new list with a specific type and initial_length carrying blocks of data_size bytes
 * 
 * @param type list_type_t
 * @param initial_length uint32_t
 * @param data_size uint32_t
 * @return list_t* 
 * 
 * @note Initial length may be negliged depending on the type of list used
 */
list_t* list_create(list_type_t type, uint32_t initial_length, uint32_t data_size, int32_t (*comparator)(const void*, const void*));

/**
 * @brief Destroy a list thus free all allocations associated with this list
 * 
 * @param list list_t*
 */
void list_destroy(list_t *list);

// Get Meta-Data

/**
 * @brief Return the type of the list
 * 
 * @param list list_t*
 * @return list_type_t 
 */
list_type_t list_get_type(const list_t *list);

/**
 * @brief Return the length of the list in other words the number of elements
 * 
 * @param list list_t*
 * @return uint32_t 
 */
uint32_t list_get_length(const list_t *list);

/**
 * @brief Return the size for one single element
 * 
 * @param list list_t*
 * @return uint32_t 
 */
uint32_t list_get_data_size(const list_t *list);

/**
 * @brief Tell if the list is sorted
 * 
 * @param list list_t*
 * @return uint8_t 
 * 
 * @note Calls add and sort are used to maintain order but add_first, add_last, insert and set can break the order
 */
uint8_t list_is_sorted(const list_t *list);

// Add Data

/**
 * @brief Add a new element in front of the list
 * 
 * @param list list_t*
 * @param element 
 * @return int8_t 
 */
int8_t list_add_first(list_t *list, void *element);

/**
 * @brief Add a new element at the end of the list
 * 
 * @param list list_t*
 * @param element 
 * @return int8_t 
 */
int8_t list_add_last(list_t *list, void *element);

/**
 * @brief Add a new element in a sorted manner
 * 
 * @param list list_t*list_t*
 * @param element void*
 * @return int8_t 
 * 
 * @note This call will produce a sorted adding only if the list is already sorted
 */
int8_t list_add(list_t *list, void *element); // Also sort data

/**
 * @brief 
 * 
 * @param list list_t*
 * @param element 
 * @param index 
 * @return int8_t 
 */
int8_t list_insert(list_t *list, void *element, uint32_t index);

// Modify Data

/**
 * @brief 
 * 
 * @param list list_t*
 * @param element 
 * @param index 
 * @return int8_t 
 */
int8_t list_set(list_t *list, void *element, uint32_t index);

// Get Data

/**
 * @brief 
 * 
 * @param list list_t*
 * @return void* 
 */
void *list_get_first(list_t *list);

/**
 * @brief 
 * 
 * @param list list_t*
 * @return void* 
 */
void *list_get_last(list_t * list);

/**
 * @brief 
 * 
 * @param list list_t*
 * @param index 
 * @return void* 
 */
void *list_get(list_t *list, uint32_t index);

/**
 * @brief 
 * 
 * @param list list_t*
 * @param element 
 * @return int8_t 
 */
int8_t list_contains(list_t *list, void *element);

/**
 * @brief 
 * 
 * @param list list_t*
 * @param element 
 * @return uint32_t 
 */
uint32_t list_find(list_t *list, void *element);

// Remove Data

/**
 * @brief 
 * 
 * @param list list_t*
 * @return int8_t 
 */
void *list_remove_first(list_t *list, void *element);

/**
 * @brief 
 * 
 * @param list list_t*
 * @return int8_t 
 */
void *list_remove_last(list_t *list, void *element);

/**
 * @brief 
 * 
 * @param list list_t*
 * @param index 
 * @return int8_t 
 */
void *list_remove(list_t *list, uint32_t index, void *element);

/**
 * @brief 
 * 
 * @param list list_t*
 * @return int8_t 
 */
int8_t list_clear(list_t *list);

// Sort Data

/**
 * @brief 
 * 
 * @param list list_t*
 * @return int8_t 
 */
int8_t list_sort(list_t *list);

#endif