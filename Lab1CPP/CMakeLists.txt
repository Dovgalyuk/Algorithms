add_executable(Lab1CPP main.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab1CPP LibraryCPPClass)

add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP PROPERTY PASS_REGULAR_EXPRESSION "Factorial array: 1 1 2 6 24 120 
Most frequent element: 2")

add_executable(TestArrayBasic tests/test_array_basic.cpp array.cpp)
target_include_directories(TestArrayBasic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME Array_basic COMMAND TestArrayBasic)

add_executable(TestArrayCopy tests/test_array_copy.cpp array.cpp)
target_include_directories(TestArrayCopy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME Array_copy COMMAND TestArrayCopy)
