add_executable(lab2cppclass Lab21Struct.cpp stack.cpp vector.cpp)
target_include_directories(lab2cppclass PUBLIC ../LibraryCPPClass)

add_test(NAME TestPlus COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_plus.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestPlus PROPERTY PASS_REGULAR_EXPRESSION "C")

add_test(NAME TestMinus COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_minus.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestMinus PROPERTY PASS_REGULAR_EXPRESSION "B")

add_test(NAME TestLeft COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_left.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestLeft PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME TestRight COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_right.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestRight PROPERTY PASS_REGULAR_EXPRESSION "B")

add_test(NAME TestInput COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_input.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_test.txt")
set_property(TEST TestInput PROPERTY PASS_REGULAR_EXPRESSION "Z")

add_test(NAME TestOutput COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_output.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestOutput PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME TestDuplicate COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_duplicate.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestDuplicate PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME TestSwap COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_swap.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestSwap PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME TestReverse COMMAND lab2cppclass "${CMAKE_CURRENT_SOURCE_DIR}/test_reverse.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input_empty.txt")
set_property(TEST TestReverse PROPERTY PASS_REGULAR_EXPRESSION "A")