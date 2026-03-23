#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "list/test_list.h"

#include "list/list.h"
#include "list/linked_list.h"

list_t *list = NULL;
list_type_t type = LINKED_LIST;
uint32_t initial_length = 0, data_size = 4;

extern int init_linked_list_suite(void) {
    type = LINKED_LIST;
    initial_length = 8;
    data_size = 4;
    return 0;
}

extern int init_array_list_suite(void) {
    type = ARRAY_LIST;
    initial_length = 8;
    data_size = 4;
    return 0;
}

extern int clean_suite(void) {
    return 0;
}

extern int32_t comparator(const void *element, const void *element2) {
    uint32_t e = *(const uint32_t*) element, e2 = *(const uint32_t*) element2;
    if (e == e2) return 0;
    else if (e < e2) return -1;
    else return 1;
}

extern int init_test(void) {
    list = list_create(type, initial_length, data_size, comparator);
    return list == NULL ? -1 : 0;
}

extern int clean_test(void) {
    if (list != NULL) {
        list_destroy(list);
        return 0;
    } else return -1;
}

extern void get_metrics_test(void) {
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_type(list), type);

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    
    CU_ASSERT_EQUAL(list_get_data_size(list), data_size);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_add_first_test(void) {
    uint32_t element = 14;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_first(list, &element));
    CU_ASSERT_EQUAL(list_get_length(list), 1);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_add_last_test(void) {
    uint32_t element = 14;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_last(list, &element));
    CU_ASSERT_EQUAL(list_get_length(list), 1);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_contains_test(void) {
    uint32_t element = 14, element2 = 16, element3 = 14;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_FALSE(list_contains(list, &element));
    CU_ASSERT_FALSE(list_contains(list, &element2));
    CU_ASSERT_FALSE(list_contains(list, &element3));

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_last(list, &element));
    CU_ASSERT_EQUAL(list_get_length(list), 1);

    CU_ASSERT_TRUE(list_contains(list, &element));
    CU_ASSERT_FALSE(list_contains(list, &element2));
    CU_ASSERT_TRUE(list_contains(list, &element3));

    CU_ASSERT_FALSE(list_add_last(list, &element2));
    CU_ASSERT_EQUAL(list_get_length(list), 2);

    CU_ASSERT_TRUE(list_contains(list, &element));
    CU_ASSERT_TRUE(list_contains(list, &element2));
    CU_ASSERT_TRUE(list_contains(list, &element3));
    
    CU_ASSERT_FALSE(clean_test());
}

extern void simple_get_first_and_get_last_test(void) {
    uint32_t element = 13, element2 = 14, element3 = 16;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_first(list), NULL);
    CU_ASSERT_EQUAL(list_get_last(list), NULL);

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_last(list, &element));
    CU_ASSERT_FALSE(list_add_first(list, &element2));
    CU_ASSERT_FALSE(list_add_last(list, &element3));
    CU_ASSERT_EQUAL(list_get_length(list), 3);

    uint32_t *e = list_get_first(list);
    CU_ASSERT_NOT_EQUAL(e, NULL);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 14);

    e = list_get_last(list);
    CU_ASSERT_NOT_EQUAL(e, NULL);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 16);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_get_test(void) {
    uint32_t element = 13, element2 = 14, element3 = 16;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_first(list), NULL);
    CU_ASSERT_EQUAL(list_get_last(list), NULL);

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_last(list, &element));
    CU_ASSERT_FALSE(list_add_first(list, &element2));
    CU_ASSERT_FALSE(list_add_last(list, &element3));
    CU_ASSERT_EQUAL(list_get_length(list), 3);

    uint32_t *e = list_get(list, 0);
    CU_ASSERT_NOT_EQUAL(e, NULL);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 14);

    e = list_get(list, 1);
    CU_ASSERT_NOT_EQUAL(e, NULL);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 13);

    e = list_get(list, 2);
    CU_ASSERT_NOT_EQUAL(e, NULL);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 16);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_insert_test(void) {
    uint32_t element = 13, element2 = 14, element3 = 16;
    CU_ASSERT_FALSE(init_test());

    CU_ASSERT_EQUAL(list_get_first(list), NULL);
    CU_ASSERT_EQUAL(list_get_last(list), NULL);

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_FALSE(list_add_last(list, &element));
    CU_ASSERT_FALSE(list_add_first(list, &element2));
    CU_ASSERT_FALSE(list_add_last(list, &element3));
    CU_ASSERT_EQUAL(list_get_length(list), 3);

    CU_ASSERT_FALSE(list_insert(list, &element, 0));
    CU_ASSERT_FALSE(list_insert(list, &element, list_get_length(list)));
    CU_ASSERT_FALSE(list_insert(list, &element, 2));

    uint32_t values[6] = {13, 14, 13, 13, 16, 13};

    uint32_t *e;
    for (uint32_t i = 0; i < 6; i++) {
        e = list_get(list, i);
        CU_ASSERT_NOT_EQUAL(e, NULL);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[i]);
    }

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_get_and_set_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    uint32_t *e;
    for (uint32_t i = 0; i < 10; i++) {
        e = list_get(list, i);
        CU_ASSERT_NOT_EQUAL(e, NULL);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[i]);

        CU_ASSERT_FALSE(list_set(list, &values[10 - i - 1], i));
    }

    for (uint32_t i = 0; i < 10; i++) {
        e = list_get(list, i);
        CU_ASSERT_NOT_EQUAL(e, NULL);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[10 - i - 1]);
    }

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_find_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {11, 38, 93, 10, 1, 0, 15, 17, 77, 99};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_EQUAL(list_find(list, &values[i]), i);
    }

    uint32_t element = 77, element2 = 70;
    CU_ASSERT_EQUAL(list_find(list, &element), 8);
    CU_ASSERT_EQUAL(list_find(list, &element2), UINT32_MAX);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_remove_first_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    uint32_t *e;
    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_EQUAL(list_get_length(list), 10 - i);

        e = list_get_first(list);
        CU_ASSERT_PTR_NOT_NULL(e);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[i]);

        e = list_remove_first(list);
        CU_ASSERT_PTR_NOT_NULL(e);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[i]);
    }

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_EQUAL(list_get_first(list), NULL);

    CU_ASSERT_PTR_NULL(list_remove_first(list));

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_remove_last_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    uint32_t *e;
    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_EQUAL(list_get_length(list), 10 - i);

        e = list_get_last(list);
        CU_ASSERT_PTR_NOT_NULL(e);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[10 - i - 1]);

        e = list_remove_last(list);
        CU_ASSERT_PTR_NOT_NULL(e);
        if (e != NULL) CU_ASSERT_EQUAL(*e, values[10 - i - 1]);
    }

    CU_ASSERT_EQUAL(list_get_length(list), 0);
    CU_ASSERT_EQUAL(list_get_last(list), NULL);

    CU_ASSERT_PTR_NULL(list_remove_last(list));

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_remove_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    uint32_t *e = list_remove(list, 5);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 25);

    e = list_remove(list, 3);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 9);

    e = list_remove(list, 10 - 2 - 1);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 81);

    e = list_remove(list, 10 - 3 - 1);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 64);

    e = list_remove(list, 0);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 0);

    e = list_remove(list, 0);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 1);

    e = list_remove(list, 0);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 4);

    e = list_remove(list, 0);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 16);

    e = list_remove(list, 1);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 49);

    e = list_remove(list, 0);
    CU_ASSERT_PTR_NOT_NULL(e);
    if (e != NULL) CU_ASSERT_EQUAL(*e, 36);

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_add_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t g = 47, p = 67;
    uint32_t values[100];
    
    values[0] = g;
    CU_ASSERT_FALSE(list_add(list, &values[0]));

    for (uint32_t i = 1; i < 100; i++) {
        values[i] = (values[i - 1] * g) % p;
        CU_ASSERT_FALSE(list_add(list, &values[i]));
    }

    for (uint32_t i = 1; i < 100; i++) {
        CU_ASSERT_TRUE(
            comparator(
                list_get(list, i - 1),
                list_get(list, i)
            ) <= 0
        );
    }

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_clear_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t values[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

    for (uint32_t i = 0; i < 10; i++) {
        CU_ASSERT_FALSE(list_add_last(list, &values[i]));
    }

    CU_ASSERT_EQUAL(list_get_length(list), 10);
    CU_ASSERT_FALSE(list_clear(list));
    CU_ASSERT_EQUAL(list_get_length(list), 0);

    CU_ASSERT_PTR_NULL(list_get_first(list));
    CU_ASSERT_PTR_NULL(list_get_last(list));
    CU_ASSERT_PTR_NULL(list_get(list, 4));

    CU_ASSERT_FALSE(clean_test());
}

extern void simple_sort_test(void) {
    CU_ASSERT_FALSE(init_test());

    uint32_t g = 47, p = 67;
    uint32_t values[100];
    
    values[0] = g;
    CU_ASSERT_FALSE(list_add_last(list, &values[0]));

    for (uint32_t i = 1; i < 100; i++) {
        values[i] = (values[i - 1] * g) % p;
        CU_ASSERT_FALSE(list_add_first(list, &values[i]));
    }

    CU_ASSERT_FALSE(list_sort(list));

    for (uint32_t i = 1; i < 100; i++) {
        CU_ASSERT_TRUE(
            comparator(
                list_get(list, i - 1),
                list_get(list, i)
            ) <= 0
        );
    }

    CU_ASSERT_FALSE(clean_test());
}

extern void make_list_suite(list_type_t list_type) {
    char *name;
    int (*init_suite) (void);
    switch (list_type) {
        case LINKED_LIST: name = "Test linked list"; init_suite = init_linked_list_suite; break;
        case ARRAY_LIST: name = "Test array list"; init_suite = init_array_list_suite; break;
        default: {
            fprintf(stderr, "Error: Invalid list type %d\n", list_type);
            return;
        }
    }

    CU_pSuite suite = CU_add_suite(name, init_suite, clean_suite);
    CU_add_test(suite, "Get metrics test", get_metrics_test);
    CU_add_test(suite, "Simple add first test", simple_add_first_test);
    CU_add_test(suite, "Simple add last test", simple_add_last_test);
    CU_add_test(suite, "Simple contains test", simple_contains_test);
    CU_add_test(suite, "Simple get first and get last test", simple_get_first_and_get_last_test);
    CU_add_test(suite, "Simple get test", simple_get_test);
    CU_add_test(suite, "Simple insert test", simple_insert_test);
    CU_add_test(suite, "Simple get and set test", simple_get_and_set_test);
    CU_add_test(suite, "Simple find test", simple_find_test);
    CU_add_test(suite, "Simple remove first test", simple_remove_first_test);
    CU_add_test(suite, "Simple remove last test", simple_remove_last_test);
    CU_add_test(suite, "Simple remove test", simple_remove_test);
    CU_add_test(suite, "Simple add test", simple_add_test);
    CU_add_test(suite, "Simple clear test", simple_clear_test);
    CU_add_test(suite, "Simple sort test", simple_sort_test);
}