add_executable(Task1 main.cpp)

target_include_directories(Task1 PUBLIC ../../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_test(NAME Test1Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt)
set_property(TEST Test1Task1 PROPERTY PASS_REGULAR_EXPRESSION "Среднее положительных элементов: 3.00.*Среднее отрицательных элементов: -3.00")

add_test(NAME Test2Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt)
set_property(TEST Test2Task1 PROPERTY PASS_REGULAR_EXPRESSION "Среднее положительных элементов: 4.00.*Отрицательных элементов не было.")

add_test(NAME Test3Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt)
set_property(TEST Test3Task1 PROPERTY PASS_REGULAR_EXPRESSION "Среднее положительных элементов: 7.50.*Среднее отрицательных элементов: -7.50")
