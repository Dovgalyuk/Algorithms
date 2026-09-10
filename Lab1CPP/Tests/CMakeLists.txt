add_executable(MyTestLab1CPP
        tests.cpp
        ../Task1/task1.cpp
        ../Task2/task2.cpp
)

add_executable(
        ProgramTests
        program_tests.cpp
)

target_include_directories(MyTestLab1CPP PUBLIC
        ../../LibraryCPP
        ../Task1
        ../Task2
        ../reader
)

target_link_libraries(MyTestLab1CPP
        LibraryCPP
)

add_test(
        NAME MyTestLab1CPP
        COMMAND $<TARGET_FILE:MyTestLab1CPP>
)

add_test(
        NAME ProgramTests
        COMMAND $<TARGET_FILE:ProgramTests>
        $<TARGET_FILE:Task1>
        $<TARGET_FILE:Task2>
)

set_tests_properties(
        MyTestLab1CPP
        PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)