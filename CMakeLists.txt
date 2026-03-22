cmake_minimum_required(VERSION 3.9)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_program(GCC_PATH gcc)

project(calgorithmslib VERSION 0.0.0 DESCRIPTION "C algorithms")

add_library(calgorithmslib)

target_compile_options(calgorithmslib PRIVATE
    # -Wall
    # -Werror
    # -Wextra
    # -Wpedantic
    -lcunit
    -O0
)

target_include_directories(calgorithmslib PUBLIC include)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
