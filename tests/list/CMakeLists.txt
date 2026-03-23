set(list_variants linked array)

target_sources(calgorithmslib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_list.c
)

foreach(variant ${list_variants})
    message(STATUS "Build test for '${variant}' list")

    add_executable(test_${variant}_list
        ${CMAKE_CURRENT_SOURCE_DIR}/test_${variant}_list.c
    )
    target_link_libraries(test_${variant}_list PRIVATE calgorithmslib cunit)
    add_test(NAME test_${variant}_list COMMAND test_${variant}_list)
endforeach()
