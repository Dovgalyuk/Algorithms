add_executable(Lab2 main.cpp)

add_test(NAME VM_Basic COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set_property(TEST VM_Basic PROPERTY PASS_REGULAR_EXPRESSION "Variables: 10 5 0 0")

add_test(NAME VM_Arithmetic COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_arithmetic.txt")
set_property(TEST VM_Arithmetic PROPERTY PASS_REGULAR_EXPRESSION "Stack: 18")

add_test(NAME VM_CallReturn COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_call_return.txt")
set_property(TEST VM_CallReturn PROPERTY PASS_REGULAR_EXPRESSION "Variables: 0 0 0 0")

add_test(NAME VM_BadReturn COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_invalid_return.txt")
set_tests_properties(VM_BadReturn PROPERTIES WILL_FAIL TRUE)

add_test(NAME VM_DivideByZero COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_division_by_zero.txt")
set_tests_properties(VM_DivideByZero PROPERTIES WILL_FAIL TRUE)

add_executable(ListStack_Check container_tests.cpp)
target_include_directories(ListStack_Check PUBLIC ../LibraryCPPClass)
target_link_libraries(ListStack_Check LibraryCPPClass)
add_test(NAME ListStack_Check COMMAND ListStack_Check)

add_test(NAME VM_Variables COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_load_store.txt")
set_property(TEST VM_Variables PROPERTY PASS_REGULAR_EXPRESSION "Variables: 10 5 15 0")

add_test(NAME VM_StackOps COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_stack_ops.txt")
set_property(TEST VM_StackOps PROPERTY PASS_REGULAR_EXPRESSION "Stack: -6 4")

add_test(NAME VM_BadCall COMMAND Lab2 "${CMAKE_CURRENT_SOURCE_DIR}/input_invalid_call.txt")
set_tests_properties(VM_BadCall PROPERTIES WILL_FAIL TRUE)
