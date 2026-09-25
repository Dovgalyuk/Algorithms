add_executable(Lab1C_Task1 lab1_task1.cpp tasks.cpp)
target_include_directories(Lab1C_Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_Task1 LibraryCPP)

add_executable(Lab1C_Task2 lab1_task2.cpp tasks.cpp)
target_include_directories(Lab1C_Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_Task2 LibraryCPP)

add_test(NAME TestLab1C_Task1_1
         COMMAND Lab1C_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1C_Task1_1
             PROPERTY PASS_REGULAR_EXPRESSION "1 3 5 7 9")

add_test(NAME TestLab1C_Task2_1
         COMMAND Lab1C_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1C_Task2_1
             PROPERTY PASS_REGULAR_EXPRESSION "0 0 1 2")

add_test(NAME TestLab1C_Task1_2
         COMMAND Lab1C_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1C_Task1_2
             PROPERTY PASS_REGULAR_EXPRESSION "0 2 4")

add_test(NAME TestLab1C_Task2_2
         COMMAND Lab1C_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1C_Task2_2
             PROPERTY PASS_REGULAR_EXPRESSION "2 3 4 5 0")