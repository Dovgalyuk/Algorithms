add_test(
    NAME MachineTest1
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input1.txt
)

set_tests_properties(
    MachineTest1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "stack:\n1\nvars:\n5\n0\n0\n0"
)

add_test(
    NAME MachineTest2
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input2.txt
)

set_tests_properties(
    MachineTest2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "stack:\n6\nvars:\n0\n0\n0\n0"
)

add_test(
    NAME MachineTest3
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input3.txt
)

set_tests_properties(
    MachineTest3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "stack:\n2\nvars:\n0\n0\n0\n0"
)

add_test(
    NAME MachineTest4
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input4.txt
)

set_tests_properties(
    MachineTest4
    PROPERTIES
    PASS_REGULAR_EXPRESSION "stack:\n10\nvars:\n10\n0\n0\n0"
)

add_test(
    NAME MachineTest5
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input5.txt
)

set_tests_properties(
    MachineTest5
    PROPERTIES
    PASS_REGULAR_EXPRESSION "stack:\n1\n2\nvars:\n0\n0\n0\n0"
)

add_test(
    NAME MachineErrorTest1
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input6.txt
)

set_tests_properties(
    MachineErrorTest1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "error: pop: stack is empty"
)

add_test(
    NAME MachineErrorTest2
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input7.txt
)

set_tests_properties(
    MachineErrorTest2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "error: istore: stack is empty"
)

add_test(
    NAME MachineErrorTest3
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input8.txt
)

set_tests_properties(
    MachineErrorTest3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "error: iadd: stack is empty"
)

add_test(
    NAME MachineErrorTest4
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input9.txt
)

set_tests_properties(
    MachineErrorTest4
    PROPERTIES
    PASS_REGULAR_EXPRESSION "error: return: no return address"
)

add_test(
    NAME MachineErrorTest5
    COMMAND Machin ${CMAKE_CURRENT_SOURCE_DIR}/machine_input10.txt
)

set_tests_properties(
    MachineErrorTest5
    PROPERTIES
    PASS_REGULAR_EXPRESSION "error: invokestatic: invalid address"
)