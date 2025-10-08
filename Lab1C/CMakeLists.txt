add_executable(Lab1C lab1.c)
target_link_libraries(Lab1C PRIVATE LibraryC)
target_include_directories(Lab1C PRIVATE ../LibraryC)

add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_tests_properties(TestLab1C PROPERTIES PASS_REGULAR_EXPRESSION
"Precipitation per month:\n78 0 0 0 0 0 0 0 0 0 0 0\nCompressed array:\n1 6 7 8 9 10 11 12 0 0 0 0"
)
