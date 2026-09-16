cmake_minimum_required(VERSION 3.15)
project(Algorithms)

enable_testing()
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if (MSVC)
    # needs at least cmake 3.15
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wno-gnu-empty-struct -Wno-unused-parameter -ftrapv)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fsanitize=address,undefined,leak)
        add_link_options(-fsanitize=address,undefined,leak)
    endif()
endif()

add_subdirectory(LibraryC)
add_subdirectory(LibraryCPP)
add_subdirectory(LibraryCPPClass)
add_subdirectory(LibraryCPPTemplate)

add_subdirectory(Lab1C)



add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)


# target_link_libraries(task1 LibraryC)
# target_link_libraries(task2 LibraryC)

add_test(
    NAME grades_test
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output.txt
)
add_test(
    NAME grades_check
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_expected.txt
)
set_tests_properties(grades_check PROPERTIES DEPENDS grades_test)

add_test(
    NAME grades_test_2
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_input_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output_2.txt
)
add_test(
    NAME grades_check_2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/grades_output_2.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/grades_expected_2.txt
)
set_tests_properties(grades_check_2 PROPERTIES DEPENDS grades_test_2)

add_test(
    NAME rle_test
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output.txt
)
add_test(
    NAME rle_check
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_expected.txt
)
set_tests_properties(rle_check PROPERTIES DEPENDS rle_test)

add_test(
    NAME rle_test_2
    COMMAND task2
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_input_2.txt
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output_2.txt
)
add_test(
    NAME rle_check_2
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/rle_output_2.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/rle_expected_2.txt
)
set_tests_properties(rle_check_2 PROPERTIES DEPENDS rle_test_2)
