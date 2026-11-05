add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)

target_link_libraries(Lab3CPP LibraryCPP)

add_test(
    NAME TestLab3CPP
    COMMAND Lab3CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
)

set_property(
    TEST TestLab3CPP
    PROPERTY PASS_REGULAR_EXPRESSION
    "2[\r\n ]+1 2 5[\r\n ]+3 4"
)