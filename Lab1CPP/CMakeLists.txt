add_executable(Lab1CPP main.cpp array.cpp)

add_test(NAME TestLab1CPP COMMAND Lab1CPP "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")

set_tests_properties(TestLab1CPP PROPERTIES
  PASS_REGULAR_EXPRESSION "Sum of digits: 17;Most frequent: 2")

add_executable(TestArrayBasic
    "${CMAKE_SOURCE_DIR}/LibraryCPPClass/Tests/array.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/array.cpp"
)
target_include_directories(TestArrayBasic PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME Array_basic COMMAND TestArrayBasic)