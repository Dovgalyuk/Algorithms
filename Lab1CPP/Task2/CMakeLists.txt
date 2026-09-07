add_executable(Task2 main.cpp)

target_include_directories(Task2 PUBLIC ../../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

add_test(NAME Test1Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt)
set_property(TEST Test1Task2 PROPERTY PASS_REGULAR_EXPRESSION "Максимальная сумма пяти соседних элементов: 40")

add_test(NAME Test2Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt)
set_property(TEST Test2Task2 PROPERTY PASS_REGULAR_EXPRESSION "Массив меньше пяти элементов.")

add_test(NAME Test3Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt)
set_property(TEST Test3Task2 PROPERTY PASS_REGULAR_EXPRESSION "Максимальная сумма пяти соседних элементов: -15")
