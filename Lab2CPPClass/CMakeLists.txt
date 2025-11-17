add_executable(lab2cppclass Lab21Struct.cpp stack.cpp vector.cpp)
target_include_directories(lab2cppclass PUBLIC ../LibraryCPPClass)

add_test(NAME Test1 COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/script1.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input1.txt")
set_property(TEST Test1 PROPERTY PASS_REGULAR_EXPRESSION "C")

add_test(NAME Test2 COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/script2.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input2.txt")
set_property(TEST Test2 PROPERTY PASS_REGULAR_EXPRESSION "X")