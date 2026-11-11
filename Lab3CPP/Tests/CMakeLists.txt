add_executable(
        ProgramTests
        program_tests.cpp
)

add_executable(
        UnitTests
        unit_tests.cpp
        ../task.cpp
)

target_include_directories(UnitTests PUBLIC
        ../../LibraryCPP
        ../
)

target_link_libraries(UnitTests
        LibraryCPP
)

add_test(
        NAME ProgramTests
        COMMAND $<TARGET_FILE:ProgramTests>
        $<TARGET_FILE:Lab3CPP>
)

add_test(
        NAME UnitTests
        COMMAND $<TARGET_FILE:UnitTests>
        $<TARGET_FILE:Lab3CPP>
)

set_tests_properties(
        ProgramTests
        PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_tests_properties(
        UnitTests
        PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)