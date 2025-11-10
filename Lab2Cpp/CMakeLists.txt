add_executable(Lab2Cpp lab2.cpp)
target_include_directories(Lab2Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab2Cpp LibraryCPP)

add_test(NAME TestLab2Cpp_1 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2Cpp_1 PROPERTY PASS_REGULAR_EXPRESSION "1.*3.*2")

add_test(NAME TestLab2Cpp_2 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2Cpp_2 PROPERTY PASS_REGULAR_EXPRESSION "1.*2.*3.*6")

add_test(NAME TestLab2Cpp_3 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab2Cpp_3 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestLab2Cpp_4 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2Cpp_4 PROPERTY PASS_REGULAR_EXPRESSION "2.*3")

add_test(NAME TestLab2Cpp_5 COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab2Cpp_5 PROPERTY PASS_REGULAR_EXPRESSION "4")
