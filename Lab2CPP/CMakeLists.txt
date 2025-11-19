add_executable(Lab2CPP main.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPP LibraryCPPClass)


add_test(NAME Test1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script1.as 
                                    ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_tests_properties(Test1 PROPERTIES PASS_REGULAR_EXPRESSION "C.*B.*A")

add_test(NAME Test2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script2.as
                                    ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_tests_properties(Test2 PROPERTIES PASS_REGULAR_EXPRESSION "C.*B.*A")

add_test(NAME Test3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script3.as
                                    ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)
set_tests_properties(Test3 PROPERTIES PASS_REGULAR_EXPRESSION "B.*A")

add_test(NAME Test4 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script4.as
                                    ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)
set_tests_properties(Test4 PROPERTIES PASS_REGULAR_EXPRESSION "A")

add_test(NAME Test5 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/script5.as
                                    ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt
)
set_tests_properties(Test5 PROPERTIES PASS_REGULAR_EXPRESSION "X.*X")