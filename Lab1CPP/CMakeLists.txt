add_executable(Task1 task1.cpp)
target_include_directories(Task1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Task1 LibraryCPP)

add_executable(Task2 task2.cpp)
target_include_directories(Task2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Task2 LibraryCPP)


add_test(NAME TestTask1_input
         COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestTask1_input PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 4.5")

add_test(NAME TestTask2_input
         COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestTask2_input PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 0")

add_test(NAME TestTask1_test1
         COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestTask1_test1 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 4.5")

add_test(NAME TestTask2_test1
         COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestTask2_test1 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 0")

add_test(NAME TestTask1_test2
         COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestTask1_test2 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 3.25")

add_test(NAME TestTask2_test2
         COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestTask2_test2 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 5")

add_test(NAME TestTask1_test3
         COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestTask1_test3 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 2.5")

add_test(NAME TestTask2_test3
         COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestTask2_test3 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 1")