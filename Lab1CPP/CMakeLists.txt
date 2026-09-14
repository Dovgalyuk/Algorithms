add_executable(task1 task1.cpp)
target_include_directories(task1 PUBLIC ../LibraryCPP)
target_link_libraries(task1 LibraryCPP)

add_executable(task2 task2.cpp)
target_include_directories(task2 PUBLIC ../LibraryCPP)
target_link_libraries(task2 LibraryCPP)

add_test(NAME Task1_Case1_Normal COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input1.txt)
set_property(TEST Task1_Case1_Normal PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Task1_Case2_PositiveOnly COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input2.txt)
set_property(TEST Task1_Case2_PositiveOnly PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Task1_Case3_AllNegative COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input3.txt)
set_property(TEST Task1_Case3_AllNegative PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME Task1_Case4_EqualAbsAndMax COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input4.txt)
set_property(TEST Task1_Case4_EqualAbsAndMax PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Task1_Case5_SingleElementNegative COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/input5.txt)
set_property(TEST Task1_Case5_SingleElementNegative PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME Task1_Case6_FileNotFound COMMAND task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task1/does_not_exist.txt)
set_tests_properties(Task1_Case6_FileNotFound PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")

add_test(NAME Task1_Case7_MissingArgument COMMAND task1)
set_tests_properties(Task1_Case7_MissingArgument PROPERTIES PASS_REGULAR_EXPRESSION "Usage:")

add_test(NAME Task2_Case1_AtEnd COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input1.txt)
set_property(TEST Task2_Case1_AtEnd PROPERTY PASS_REGULAR_EXPRESSION "3 4 5 10 20")

add_test(NAME Task2_Case2_AtBeginning COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input2.txt)
set_property(TEST Task2_Case2_AtBeginning PROPERTY PASS_REGULAR_EXPRESSION "10 20 30 40 50")

add_test(NAME Task2_Case3_ExactFive COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input3.txt)
set_property(TEST Task2_Case3_ExactFive PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")

add_test(NAME Task2_Case4_NegativeNumbers COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input4.txt)
set_property(TEST Task2_Case4_NegativeNumbers PROPERTY PASS_REGULAR_EXPRESSION "-2 -3 -4 -5 -1")

add_test(NAME Task2_Case5_InMiddle COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/input5.txt)
set_property(TEST Task2_Case5_InMiddle PROPERTY PASS_REGULAR_EXPRESSION "5 6 7 8 9")

add_test(NAME Task2_Case6_FileNotFound COMMAND task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/task2/does_not_exist.txt)
set_tests_properties(Task2_Case6_FileNotFound PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")

add_test(NAME Task2_Case7_MissingArgument COMMAND task2)
set_tests_properties(Task2_Case7_MissingArgument PROPERTIES PASS_REGULAR_EXPRESSION "Usage:")