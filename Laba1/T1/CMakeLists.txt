add_executable(Task1 main.cpp)

target_include_directories(Task1 PUBLIC ../../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_test(NAME Test1Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt)
set_property(TEST Test1Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "Среднее в первой декаде: 5\nСреднее во второй декаде: 6\nСреднее в третьей декаде: 7")

add_test(NAME Test2Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt)
set_property(TEST Test2Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "Среднее в первой декаде: 0\nСреднее во второй декаде: 0\nСреднее в третьей декаде: 0")

add_test(NAME Test3Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt)
set_property(TEST Test3Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "Среднее в первой декаде: 2.5\nСреднее во второй декаде: 3.1\nСреднее в третьей декаде: 4")