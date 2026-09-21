add_executable(lab1_task1 lab1_task1.cpp)
target_include_directories(lab1_task1 PUBLIC ../LibraryCPP)
target_link_libraries(lab1_task1 LibraryCPP)

add_executable(lab1_task2 lab1_task2.cpp)
target_include_directories(lab1_task2 PUBLIC ../LibraryCPP)
target_link_libraries(lab1_task2 LibraryCPP)

add_test(NAME TestTask1 COMMAND lab1_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestTask1 PROPERTY PASS_REGULAR_EXPRESSION "5\\.454545")

add_test(NAME TestTask2 COMMAND lab1_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestTask2 PROPERTY PASS_REGULAR_EXPRESSION "\\(1,2\\) \\(2,1\\) \\(3,1\\)")
