add_executable(lab1cppclass struct1.cpp)
target_include_directories(lab1cppclass PUBLIC ../LibraryCPPClass)
target_link_libraries(lab1cppclass LibraryCPPClass)

add_test(NAME TestLab1CPPClass COMMAND lab1cppclass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPPClass PROPERTY PASS_REGULAR_EXPRESSION "12 4")

add_test(NAME TestLab1CPPClass1 COMMAND lab1cppclass ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1CPPClass1 PROPERTY PASS_REGULAR_EXPRESSION "3 2")