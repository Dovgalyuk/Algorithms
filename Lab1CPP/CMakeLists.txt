add_executable(Lab1CPP_Task1 Task1/task1.cpp Tests/main_task1.cpp)
target_include_directories(Lab1CPP_Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task1 LibraryCPP)

add_executable(Lab1CPP_Task2 Task2/task2.cpp Tests/main_task2.cpp)
target_include_directories(Lab1CPP_Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task2 LibraryCPP)

# Тест 1
add_test(NAME TestLab1CPP_Task1 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP_Task1 PROPERTY PASS_REGULAR_EXPRESSION 
[=[\[0\] = 2
\[1\] = 4
\[2\] = 6
\[3\] = 8
\[4\] = 10
\[5\] = 12
\[6\] = 14
\[7\] = 16
\[8\] = 18
\[9\] = 20]=]
)

# Тест 2
add_test(NAME Test2Lab1CPP_Task1 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2Lab1CPP_Task1 PROPERTY PASS_REGULAR_EXPRESSION 
[=[\[0\] = 2
\[1\] = 4
\[2\] = 6
\[3\] = 8
\[4\] = 10]=]
)

# Тест 3
add_test(NAME TestLab1CPP_Task2 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP_Task2 PROPERTY PASS_REGULAR_EXPRESSION 
[=[\[0\] = 1
\[1\] = 2
\[2\] = 3
\[3\] = 4
\[4\] = 5
\[5\] = 6
\[6\] = 7
\[7\] = 8
\[8\] = 9
\[9\] = 0]=]
)

# Тест 4
add_test(NAME Test2Lab1CPP_Task2 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2Lab1CPP_Task2 PROPERTY PASS_REGULAR_EXPRESSION 
[=[\[0\] = 1
\[1\] = 2
\[2\] = 3
\[3\] = 4
\[4\] = 5]=]
)
