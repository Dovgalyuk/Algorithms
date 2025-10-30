add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)



add_test(NAME Lab2_Test1_BasicNumbers COMMAND Lab2CPP ${CMAKE_CURRENT_BINARY_DIR}/tests/test1.txt)
set_property(TEST Lab2_Test1_BasicNumbers PROPERTY PASS_REGULAR_EXPRESSION "3.*2.*1")


add_test(NAME Lab2_Test2_Arithmetic COMMAND Lab2CPP ${CMAKE_CURRENT_BINARY_DIR}/tests/test2.txt)
set_property(TEST Lab2_Test2_Arithmetic PROPERTY PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

add_test(NAME Lab2_Test3_3 COMMAND Lab2CPP ${CMAKE_CURRENT_BINARY_DIR}/tests/test3.txt)
set_property(TEST Lab2_Test3_Multiplication PROPERTY PASS_REGULAR_EXPRESSION "10")


add_test(NAME Lab2_Test4_Subtraction COMMAND Lab2CPP ${CMAKE_CURRENT_BINARY_DIR}/tests/test4.txt)
set_property(TEST Lab2_Test4_Subtraction PROPERTY PASS_REGULAR_EXPRESSION "8")


add_test(NAME Lab2_Test5_Logical COMMAND Lab2CPP ${CMAKE_CURRENT_BINARY_DIR}/tests/test5.txt)
set_property(TEST Lab2_Test5_Logical PROPERTY PASS_REGULAR_EXPRESSION "1.*1")