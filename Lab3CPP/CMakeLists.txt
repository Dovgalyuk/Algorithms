add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME shortest_path_example
         COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(shortest_path_example PROPERTIES
    PASS_REGULAR_EXPRESSION "^2[ \t\r\n]*$")
