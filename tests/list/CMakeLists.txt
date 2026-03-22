add_executable(test_lists
    ${CMAKE_CURRENT_SOURCE_DIR}/test_list.c
)
target_link_libraries(test_lists PRIVATE calgorithmslib cunit)
add_test(NAME test_lists COMMAND test_lists)
