add_executable(Lab2C lab2.c)
target_include_directories(Lab2C PUBLIC ../LibraryC)
target_link_libraries(Lab2C LibraryC)

add_test(NAME ProcCase1 COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input_proc1.txt)
set_property(TEST ProcCase1 PROPERTY PASS_REGULAR_EXPRESSION "A = 0\nB = 1\nC = 0\nD = 0")

add_test(NAME ProcCase2 COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input_proc2.txt)
set_property(TEST ProcCase2 PROPERTY PASS_REGULAR_EXPRESSION "A = 0\nB = 2\nC = 1\nD = 1")

add_test(NAME ProcCase3 COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input_proc3.txt)
set_property(TEST ProcCase3 PROPERTY PASS_REGULAR_EXPRESSION "A = 0\nB = 3\nC = 0\nD = 0")

add_test(NAME ProcCase4_SUB COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input_proc4.txt)
set_property(TEST ProcCase4_SUB PROPERTY PASS_REGULAR_EXPRESSION "A = 3\nB = 0\nC = 0\nD = 0")

add_test(NAME ProcCase5_Mixed COMMAND Lab2C ${CMAKE_CURRENT_SOURCE_DIR}/input_proc5.txt)
set_property(TEST ProcCase5_Mixed PROPERTY PASS_REGULAR_EXPRESSION "A = 3\nB = 21\nC = 0\nD = 0")
