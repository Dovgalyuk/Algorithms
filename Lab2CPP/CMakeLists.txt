add_executable(Lab2CPP_Task
    Task/task.cpp
)

target_link_libraries(Lab2CPP_Task PRIVATE LibraryCPP)

target_include_directories(Lab2CPP_Task PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

add_test(NAME TestLab2CPP_Task_Example
    COMMAND Lab2CPP_Task ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input.txt)
set_property(TEST TestLab2CPP_Task_Example PROPERTY PASS_REGULAR_EXPRESSION 
[=[4 8
9 10
Total: 2]=]
)

add_test(NAME TestLab2CPP_Task_AllCollide
    COMMAND Lab2CPP_Task ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_2.txt)
set_property(TEST TestLab2CPP_Task_AllCollide PROPERTY PASS_REGULAR_EXPRESSION 
[=[2 3
Total: 1]=]
)

add_test(NAME TestLab2CPP_Task_NoneCollide
    COMMAND Lab2CPP_Task ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_3.txt)
set_property(TEST TestLab2CPP_Task_NoneCollide PROPERTY PASS_REGULAR_EXPRESSION "Total: 0")

add_test(NAME TestLab2CPP_Task_Nested
    COMMAND Lab2CPP_Task ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_4.txt)
set_property(TEST TestLab2CPP_Task_Nested PROPERTY PASS_REGULAR_EXPRESSION 
[=[2 3
1 4
5 6
Total: 3]=]
)