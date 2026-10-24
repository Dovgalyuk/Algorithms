cmake_minimum_required(VERSION 3.10)
project(Lab1CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../LibraryCPP/Tests ${CMAKE_BINARY_DIR}/LibraryCPP_Tests)

add_executable(task1 task1.cpp)
target_include_directories(task1 PUBLIC ../LibraryCPP)
target_link_libraries(task1 PRIVATE LibraryCPP)

add_executable(task2 task2.cpp)
target_include_directories(task2 PUBLIC ../LibraryCPP)
target_link_libraries(task2 PRIVATE LibraryCPP)

enable_testing()

add_test(NAME test1_task1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input11.txt
)
set_property(TEST test1_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "2 3 5 7 11 0 0 0 0 0 ")

add_test(NAME test2_task1
    COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input12.txt
)
set_property(TEST test2_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "2 3 5 7 11 13 17 19 0 0 0 0 0 0 0 0 0 0 0 0 ")

# ── Тесты для task2 ──────────────────────────────────────
add_test(NAME test1_task2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input21.txt
)
set_property(TEST test1_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "2")

add_test(NAME test2_task2
    COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input22.txt
)
set_property(TEST test2_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "1")
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS Lab1CPP
    COMMENT "Running all tests..."
)