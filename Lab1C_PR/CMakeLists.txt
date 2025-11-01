add_executable(Lab1C_PR main.cpp)
target_include_directories(Lab1C_PR PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_PR LibraryCPP)

if (MSVC)
  target_compile_options(Lab1C_PR PRIVATE /utf-8)
endif()

add_test(NAME TestLab1C_PR COMMAND Lab1C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C_PR PROPERTY PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114")

add_test(NAME TestLab1C_PR_Task4_Pos COMMAND Lab1C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input_task4.txt)
set_tests_properties(TestLab1C_PR_Task4_Pos PROPERTIES PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(1\\): 1;Номера \\(от 0\\): 0")