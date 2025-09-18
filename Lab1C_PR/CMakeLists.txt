set(ENABLE_TESTING OFF)

add_subdirectory(../LibraryCPP LibraryCPP)

add_executable(Lab1C_PR main.cpp)
target_include_directories(Lab1C_PR PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C_PR LibraryCPP)

enable_testing()

add_test(NAME TestLab1C_PR COMMAND Lab1C_PR ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1C_PR PROPERTY PASS_REGULAR_EXPRESSION "Task 4: Количество элементов > суммы \\(.*\\): 0;Task 5: Максимальная сумма 5 соседних: 114")