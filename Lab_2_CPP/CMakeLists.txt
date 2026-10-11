add_executable(Lab_2_CPP lab2.cpp)

target_include_directories(Lab_2_CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab_2_CPP PRIVATE LibraryCPP)

add_test(NAME Lab2_Test1 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_input.txt)
set_tests_properties(Lab2_Test1 PROPERTIES PASS_REGULAR_EXPRESSION "Hello, world!")

add_test(NAME Lab2_Test2 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_input.txt)
set_tests_properties(Lab2_Test2 PROPERTIES PASS_REGULAR_EXPRESSION "ABCBA")

add_test(NAME Lab2_Test3 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3_input.txt)
set_tests_properties(Lab2_Test3 PROPERTIES PASS_REGULAR_EXPRESSION "5")

add_test(NAME Lab2_Test4 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4_input.txt)
set_tests_properties(Lab2_Test4 PROPERTIES PASS_REGULAR_EXPRESSION "10")

add_test(NAME Lab2_Test5 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5_input.txt)
set_tests_properties(Lab2_Test5 PROPERTIES PASS_REGULAR_EXPRESSION "8")

add_test(NAME Lab2_Test6 COMMAND Lab_2_CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test6_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test6_input.txt)
set_tests_properties(Lab2_Test6 PROPERTIES PASS_REGULAR_EXPRESSION "0")
