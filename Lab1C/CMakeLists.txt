enable_testing()

add_executable(Lab1Task1 task1.cpp)
target_include_directories(Lab1Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task1 LibraryCPP)

add_executable(Lab1Task2 task2.cpp)
target_include_directories(Lab1Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Task2 LibraryCPP)

add_test(NAME TestTask1 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

add_test(NAME TestTask1_Test1 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestTask1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "165") # Единственное чётное число 100 на 165 индексе

add_test(NAME TestTask1_Test2 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestTask1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "76")  # Единственное чётное число 4 на 76 индексе

add_test(NAME TestTask1_Test6_20 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST TestTask1_Test6_20 PROPERTY PASS_REGULAR_EXPRESSION "20") #2 на индексе 20

add_test(NAME TestTask1_Test6_31 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST TestTask1_Test6_31 PROPERTY PASS_REGULAR_EXPRESSION "31") #4 на индексе 31

add_test(NAME TestTask1_Test6_37 COMMAND Lab1Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST TestTask1_Test6_37 PROPERTY PASS_REGULAR_EXPRESSION "37")  #8 на индексе 37

add_test(NAME TestTask2 COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

add_test(NAME TestTask2_Test3 COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestTask2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME TestTask2_Test4 COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test4.txt)
set_property(TEST TestTask2_Test4 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME TestTask2_Test5 COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test5.txt)
set_property(TEST TestTask2_Test5 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME TestTask2_Test6 COMMAND Lab1Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test6.txt)
set_property(TEST TestTask2_Test6 PROPERTY PASS_REGULAR_EXPRESSION "2")