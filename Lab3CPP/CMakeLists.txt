add_executable(Lab3CPP_Task Task/task.cpp)
target_link_libraries(Lab3CPP_Task PRIVATE LibraryCPP)

add_test(NAME TestLab3CPP_Task_Path
    COMMAND Lab3CPP_Task "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_possible.txt")
set_tests_properties(TestLab3CPP_Task_Path PROPERTIES PASS_REGULAR_EXPRESSION
    [=[^######
#xxxX#
#x####
#xxxY#
######
$]=])

add_test(NAME TestLab3CPP_Task_Impossible
    COMMAND Lab3CPP_Task "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_impossible.txt")
set_tests_properties(TestLab3CPP_Task_Impossible PROPERTIES PASS_REGULAR_EXPRESSION
    [=[^IMPOSSIBLE
$]=])
