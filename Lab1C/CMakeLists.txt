add_executable(Lab1C lab1.cpp)
target_link_libraries(Lab1C LibraryCPP)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1C PROPERTIES PASS_REGULAR_EXPRESSION "Task1: element closest to average \\(2\\.50\\) is 2[\r\n]*Task2: shifted array = 3 4 0 0")

add_test(NAME TestLab1C_2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(TestLab1C_2 PROPERTIES PASS_REGULAR_EXPRESSION "Task1: element closest to average \\(25\\.00\\) is 20[\r\n]*Task2: shifted array = 0 10 20 30")