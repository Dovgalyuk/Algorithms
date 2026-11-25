add_executable(Task1 Task1/main.cpp)
target_link_libraries(Task1 LibraryCPPClass)
target_include_directories(Task1 PUBLIC ../LibraryCPPClass)

add_test(NAME Task1Test COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Task1/tests/input1.txt)
add_test(NAME Task1Test2 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Task1/tests/input2.txt)
add_test(NAME Task1Test3 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Task1/tests/input3.txt)

set_tests_properties(Task1Test PROPERTIES
    PASS_REGULAR_EXPRESSION "2"
)
set_tests_properties(Task1Test2 PROPERTIES
    PASS_REGULAR_EXPRESSION "5"
)
set_tests_properties(Task1Test3 PROPERTIES
    PASS_REGULAR_EXPRESSION "0"
)

add_executable(Task2 Task2/main.cpp)
target_link_libraries(Task2 LibraryCPPClass)
target_include_directories(Task2 PUBLIC ../LibraryCPPClass)

add_test(NAME Task2Test COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Task2/tests/input1.txt)
add_test(NAME Task2Test2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Task2/tests/input2.txt)
add_test(NAME Task2Test3 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Task2/tests/input3.txt)

set_tests_properties(Task2Test PROPERTIES
    PASS_REGULAR_EXPRESSION "2"
)
set_tests_properties(Task2Test2 PROPERTIES
    PASS_REGULAR_EXPRESSION "2"
)
set_tests_properties(Task2Test3 PROPERTIES
    PASS_REGULAR_EXPRESSION "Not enough even elements"
)