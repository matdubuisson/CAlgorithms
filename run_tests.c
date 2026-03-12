#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "Test/Test.h"

static void intro_test(void) {
    CU_PASS("Success");
}

int main(void) {
    CU_initialize_registry();

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_pSuite suite = CU_add_suite("Simple tests", 0, 0);
    CU_add_test(suite, "Introduction test", intro_test);

    LIST_test();

    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}