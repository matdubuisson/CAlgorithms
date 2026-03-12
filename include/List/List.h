#ifndef __LIST__LIBRARY__
#define __LIST__LIBRARY__

#include <stdint.h>
#include <stddef.h>

typedef enum {
    LIST_ARRAY,
    LIST_LINKED,
    LIST_NOT_IMPLEMENTED
} ListType;

typedef enum {
    LIST_SORTED = 1
} ListFlag;

#include "List/ListArray.h"
#include "List/ListLinked.h"

typedef union ListConcrete {
    ListArray list_array;
    ListLinked list_linked;
} ListConcrete;

typedef struct List {
    ListType type;

    uint32_t length;
    uint32_t data_size;
    uint8_t flags;

    int32_t (*comparator)(const void*, const void*);

    ListConcrete concrete;
} List;

// Allocation Management

/**
 * @brief Create a new list with a specific type and initial_length carrying blocks of data_size bytes
 * 
 * @param type ListType
 * @param initial_length uint32_t
 * @param data_size uint32_t
 * @return List* 
 * 
 * @note Initial length may be negliged depending on the type of list used
 */
List* LIST_create(ListType type, uint32_t initial_length, uint32_t data_size, int32_t (*comparator)(const void*, const void*));

/**
 * @brief Destroy a list thus free all allocations associated with this list
 * 
 * @param list List*
 */
void LIST_destroy(List *list);

// Get Meta-Data

/**
 * @brief Return the type of the list
 * 
 * @param list List*
 * @return ListType 
 */
ListType LIST_get_type(const List *list);

/**
 * @brief Return the length of the list in other words the number of elements
 * 
 * @param list List*
 * @return uint32_t 
 */
uint32_t LIST_get_length(const List *list);

/**
 * @brief Return the size for one single element
 * 
 * @param list List*
 * @return uint32_t 
 */
uint32_t LIST_get_data_size(const List *list);

/**
 * @brief Tell if the list is sorted
 * 
 * @param list List*
 * @return uint8_t 
 * 
 * @note Calls add and sort are used to maintain order but add_first, add_last, insert and set can break the order
 */
uint8_t LIST_is_sorted(const List *list);

// Add Data

/**
 * @brief Add a new element in front of the list
 * 
 * @param list List*
 * @param element 
 * @return int8_t 
 */
int8_t LIST_add_first(List *list, void *element);

/**
 * @brief Add a new element at the end of the list
 * 
 * @param list List*
 * @param element 
 * @return int8_t 
 */
int8_t LIST_add_last(List *list, void *element);

/**
 * @brief Add a new element in a sorted manner
 * 
 * @param list List*List*
 * @param element void*
 * @return int8_t 
 * 
 * @note This call will produce a sorted adding only if the list is already sorted
 */
int8_t LIST_add(List *list, void *element); // Also sort data

/**
 * @brief 
 * 
 * @param list List*
 * @param element 
 * @param index 
 * @return int8_t 
 */
int8_t LIST_insert(List *list, void *element, uint32_t index);

// Modify Data

/**
 * @brief 
 * 
 * @param list List*
 * @param element 
 * @param index 
 * @return int8_t 
 */
int8_t LIST_set(List *list, void *element, uint32_t index);

// Get Data

/**
 * @brief 
 * 
 * @param list List*
 * @return void* 
 */
void *LIST_get_first(List *list);

/**
 * @brief 
 * 
 * @param list List*
 * @return void* 
 */
void *LIST_get_last(List * list);

/**
 * @brief 
 * 
 * @param list List*
 * @param index 
 * @return void* 
 */
void *LIST_get(List *list, uint32_t index);

/**
 * @brief 
 * 
 * @param list List*
 * @param element 
 * @return int8_t 
 */
int8_t LIST_contains(List *list, void *element);

/**
 * @brief 
 * 
 * @param list List*
 * @param element 
 * @return uint32_t 
 */
uint32_t LIST_find(List *list, void *element);

// Remove Data

/**
 * @brief 
 * 
 * @param list List*
 * @return int8_t 
 */
void *LIST_remove_first(List *list);

/**
 * @brief 
 * 
 * @param list List*
 * @return int8_t 
 */
void *LIST_remove_last(List *list);

/**
 * @brief 
 * 
 * @param list List*
 * @param index 
 * @return int8_t 
 */
void *LIST_remove(List *list, uint32_t index);

/**
 * @brief 
 * 
 * @param list List*
 * @return int8_t 
 */
int8_t LIST_clear(List *list);

// Sort Data

/**
 * @brief 
 * 
 * @param list List*
 * @return int8_t 
 */
int8_t LIST_sort(List *list);

#endif