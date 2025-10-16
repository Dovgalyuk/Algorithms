add_executable(Lab1C lab1.c)
target_link_libraries(Lab1C PRIVATE LibraryC)
target_include_directories(Lab1C PRIVATE ../LibraryC)

add_test(NAME TestLab1_Task1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt task1)
set_tests_properties(TestLab1_Task1 PROPERTIES PASS_REGULAR_EXPRESSION
"496 1215 2384 3165 4216 5055 6135 7225 8255 9285 10264 11235"
)

add_test(NAME TestLab1_Task2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt task2)
set_tests_properties(TestLab1_Task2 PROPERTIES PASS_REGULAR_EXPRESSION
"1 6 7 8 9 .* 0 0 0 0"
)
 