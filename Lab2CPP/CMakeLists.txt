cmake_minimum_required(VERSION 3.15)

add_executable(SimpleVM main.cpp)

target_link_libraries(SimpleVM LibraryCPP)

add_custom_command(
    OUTPUT input.txt
    COMMAND ${CMAKE_COMMAND} -E echo "bipush 1\nbipush 2\nbipush 3\niadd\nistore_0" > input.txt
    DEPENDS main.cpp
    VERBATIM
)

add_custom_target(create_input_file ALL DEPENDS input.txt)

add_test(
    NAME SimpleVMTest
    COMMAND $<TARGET_FILE:SimpleVM>
)

set_tests_properties(SimpleVMTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND_ARGS ""
    PASS_REGULAR_EXPRESSION "Executing: bipush\nExecuting: bipush\nExecuting: bipush\nExecuting: iadd\nExecuting: istore_0\nstack:\n1\nvars:\n5\n0\n0\n0"
)

add_dependencies(SimpleVMTest create_input_file)