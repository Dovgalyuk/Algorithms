add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)



add_test(NAME Lab2_Test1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST Lab2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "3\n.*2\n.*1")


add_test(NAME Lab2_Test2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST Lab2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

add_test(NAME Lab2_Test3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST Lab2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "10")


add_test(NAME Lab2_Test4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_property(TEST Lab2_Test4 PROPERTY PASS_REGULAR_EXPRESSION "8")


add_test(NAME Lab2_Test5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_property(TEST Lab2_Test5 PROPERTY PASS_REGULAR_EXPRESSION "1.*1")