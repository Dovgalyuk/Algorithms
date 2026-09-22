add_executable(Lab1Cars cars.cpp)
add_executable(Lab1Elements elements.cpp)

target_include_directories(Lab1Cars PUBLIC ../LibraryCPPClass)
target_include_directories(Lab1Elements PUBLIC ../LibraryCPPClass)

target_link_libraries(Lab1Cars LibraryCPPClass)
target_link_libraries(Lab1Elements LibraryCPPClass)

add_test(NAME Cars_Test1 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test1.txt")
add_test(NAME Cars_Test2 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test2.txt")
add_test(NAME Cars_Test3 COMMAND Lab1Cars "${CMAKE_CURRENT_SOURCE_DIR}/tests/cars_test3.txt")

add_test(NAME Elements_Test1 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test1.txt")
add_test(NAME Elements_Test2 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test2.txt")
add_test(NAME Elements_Test3 COMMAND Lab1Elements "${CMAKE_CURRENT_SOURCE_DIR}/tests/elements_test3.txt")
