cmake_minimum_required(VERSION 3.10)
project(Lab1CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Lab1Apfelbaum STATIC apfel.cpp)
target_include_directories(Lab1Apfelbaum PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP
)
target_link_libraries(Lab1Apfelbaum LibraryCPP)

add_executable(task1 task1.cpp)
target_link_libraries(task1 Lab1Apfelbaum)

add_executable(task2 task2.cpp)
target_link_libraries(task2 Lab1Apfelbaum)

enable_testing()

file(GLOB TASK1_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_*.txt" "${CMAKE_CURRENT_SOURCE_DIR}/tests/Task1_*.txt")
foreach(TEST_FILE ${TASK1_TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    string(TOLOWER "${TEST_NAME}" LOWER_TEST_NAME)

    add_test(NAME "${LOWER_TEST_NAME}" COMMAND task1)
    set_property(TEST "${LOWER_TEST_NAME}" PROPERTY ENVIRONMENT "INPUT_FILE=${TEST_FILE}")
    set_tests_properties("${LOWER_TEST_NAME}" PROPERTIES ATTACHED_FILES "${TEST_FILE}")

    if(LOWER_TEST_NAME STREQUAL "task1_test1")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "1 1 6 24 120")
    elseif(LOWER_TEST_NAME STREQUAL "task1_test2")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "720")
    elseif(LOWER_TEST_NAME STREQUAL "task1_test3")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "2 2 6 6")
    elseif(LOWER_TEST_NAME STREQUAL "task1_test4" OR LOWER_TEST_NAME STREQUAL "task1_test5")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY WILL_FAIL TRUE)
    endif()
endforeach()

file(GLOB TASK2_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_*.txt" "${CMAKE_CURRENT_SOURCE_DIR}/tests/Task2_*.txt")
foreach(TEST_FILE ${TASK2_TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    string(TOLOWER "${TEST_NAME}" LOWER_TEST_NAME)

    add_test(NAME "${LOWER_TEST_NAME}" COMMAND task2)

    if(LOWER_TEST_NAME STREQUAL "task2_test1")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "2 3 5")
    elseif(LOWER_TEST_NAME STREQUAL "task2_test2")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "7 11 13 17")
    elseif(LOWER_TEST_NAME STREQUAL "task2_test3")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "42")
    elseif(LOWER_TEST_NAME STREQUAL "task2_test4")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY PASS_REGULAR_EXPRESSION "2")
    elseif(LOWER_TEST_NAME STREQUAL "task2_test5")
        set_property(TEST "${LOWER_TEST_NAME}" PROPERTY WILL_FAIL TRUE)
    endif()
endforeach()