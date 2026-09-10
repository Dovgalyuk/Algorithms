add_executable(Task2 main.cpp)

target_include_directories(Task2 PUBLIC ../../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

add_test(NAME Test1Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt)
set_property(TEST Test1Task2 PROPERTY PASS_REGULAR_EXPRESSION "Самое часто встречающееся число: 3")

add_test(NAME Test2Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt)
set_property(TEST Test2Task2 PROPERTY PASS_REGULAR_EXPRESSION "Нет повторений")

add_test(NAME Test3Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt)
set_property(TEST Test3Task2 PROPERTY PASS_REGULAR_EXPRESSION "Самое часто встречающееся число: 7")