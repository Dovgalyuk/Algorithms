add_executable(task1 task1.cpp)
target_include_directories(task1 PUBLIC ../LibraryCPPTemplate)

add_executable(task2 task2.cpp)
target_include_directories(task2 PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestTask1_1 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestTask1_1 PROPERTY PASS_REGULAR_EXPRESSION "1 2")

add_test(NAME TestTask1_2 COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestTask1_2 PROPERTY PASS_REGULAR_EXPRESSION "-3 2 -3")

add_test(NAME TestTask2_1 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestTask2_1 PROPERTY PASS_REGULAR_EXPRESSION "1 3 5")

add_test(NAME TestTask2_2 COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestTask2_2 PROPERTY PASS_REGULAR_EXPRESSION "20 40")