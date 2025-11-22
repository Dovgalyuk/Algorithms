add_executable(Lab3Cpp lab3.cpp)
target_include_directories(Lab3Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab3Cpp LibraryCPP)

add_test(NAME TestLab3Cpp_1 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3Cpp_1 PROPERTY PASS_REGULAR_EXPRESSION "######.*#xxxX#.*#x####.*#xxxY#.*######")

add_test(NAME TestLab3Cpp_2 COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3Cpp_2 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")
