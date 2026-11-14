add_executable(Lab1Cars cars.cpp)

add_executable(Lab1Elements elements.cpp)

target_include_directories(Lab1Cars PUBLIC ../LibraryCPPClass)

target_include_directories(Lab1Elements PUBLIC ../LibraryCPPClass)

target_link_libraries(Lab1Cars LibraryCPPClass)

target_link_libraries(Lab1Elements LibraryCPPClass)

add_test(NAME Cars_Test1 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test1.txt")

set_property(TEST Cars_Test1 PROPERTY PASS_REGULAR_EXPRESSION "2 6")

add_test(NAME Cars_Test2 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test2.txt")

set_property(TEST Cars_Test2 PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME Cars_Test3 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test3.txt")

set_property(TEST Cars_Test3 PROPERTY PASS_REGULAR_EXPRESSION "1 2")

add_test(NAME Elements_Test1 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test1.txt")

set_property(TEST Elements_Test1 PROPERTY PASS_REGULAR_EXPRESSION "2 3 7")

add_test(NAME Elements_Test2 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test2.txt")

set_property(TEST Elements_Test2 PROPERTY PASS_REGULAR_EXPRESSION "3 7")

add_test(NAME Elements_Test3 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test3.txt")

set_property(TEST Elements_Test3 PROPERTY PASS_REGULAR_EXPRESSION "3 5 7 11 13")