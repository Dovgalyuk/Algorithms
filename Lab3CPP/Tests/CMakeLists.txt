add_executable(
        ProgramTests
        program_tests.cpp
)

add_test(
        NAME ProgramTests
        COMMAND $<TARGET_FILE:ProgramTests>
        $<TARGET_FILE:Lab3CPP>
)

set_tests_properties(
        ProgramTests
        PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)