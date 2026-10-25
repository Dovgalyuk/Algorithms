add_executable(Lab1CPP_Task1 task1.cpp)
target_include_directories(Lab1CPP_Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task1 LibraryCPP)

add_executable(Lab1CPP_Task2 task2.cpp)
target_include_directories(Lab1CPP_Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task2 LibraryCPP)

add_test(NAME TestTask1_1 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_1.txt)
set_property(TEST TestTask1_1 PROPERTY PASS_REGULAR_EXPRESSION "0 1 2 3 4")

add_test(NAME TestTask1_2 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_2.txt)
set_property(TEST TestTask1_2 PROPERTY PASS_REGULAR_EXPRESSION "-9 0 -4 4 -6 1")

add_test(NAME TestTask1_3 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task1_3.txt)
set_property(TEST TestTask1_3 PROPERTY PASS_REGULAR_EXPRESSION "-10 0 10 0")

add_test(NAME TestTask2_1 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_1.txt)
set_property(TEST TestTask2_1 PROPERTY PASS_REGULAR_EXPRESSION "1 5 6 0 0 0")

add_test(NAME TestTask2_2 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_2.txt)
set_property(TEST TestTask2_2 PROPERTY PASS_REGULAR_EXPRESSION "-3 10 7 -4 0 0 0 0")

add_test(NAME TestTask2_3 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_3.txt)
set_property(TEST TestTask2_3 PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4")

add_test(NAME TestTask2_4 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/tests/task2_4.txt)
set_property(TEST TestTask2_4 PROPERTY PASS_REGULAR_EXPRESSION "0 0 0 0 0")
