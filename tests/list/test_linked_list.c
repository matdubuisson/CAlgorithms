#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "list/test_list.h"

int main(void) {
    CU_initialize_registry();

    CU_basic_set_mode(CU_BRM_VERBOSE);

    make_list_suite(LINKED_LIST);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}