add_executable(Lab4CPP main.cpp)

target_include_directories(Lab4CPP PUBLIC
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME floyd_example
    COMMAND Lab4CPP "${CMAKE_SOURCE_DIR}/Lab4CPP/input.txt")