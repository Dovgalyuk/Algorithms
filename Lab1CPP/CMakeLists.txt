add_executable(Lab1CPP_task1 task1.cpp)
target_include_directories(Lab1CPP_task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_task1 LibraryCPP)

add_executable(Lab1CPP_task2 task2.cpp)
target_include_directories(Lab1CPP_task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_task2 LibraryCPP)

#тесты первого задания
add_test(NAME Task1_Test COMMAND Lab1CPP_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Task1_Test PROPERTY PASS_REGULAR_EXPRESSION "positive: 9, negative: 0, zero: 1\\.")

add_test(NAME Task1_Test2 COMMAND Lab1CPP_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_2.txt)
set_property(TEST Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "positive: 2, negative: 2, zero: 1\\.")

add_test(NAME Task1_Test3 COMMAND Lab1CPP_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_3.txt)
set_property(TEST Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION "positive: 0, negative: 0, zero: 4\\.")

add_test(NAME Task1_Test4 COMMAND Lab1CPP_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input1_4.txt)
set_property(TEST Task1_Test4 PROPERTY PASS_REGULAR_EXPRESSION "invalid input data")

#тесты второго задания
add_test(NAME Task2_Test COMMAND Lab1CPP_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Task2_Test PROPERTY PASS_REGULAR_EXPRESSION "unique: 1 2 3 4 5 6 7 8 9 0\\.")

add_test(NAME Task2_Test2 COMMAND Lab1CPP_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_2.txt)
set_property(TEST Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "unique: 1 3 5\\.")

add_test(NAME Task2_Test3 COMMAND Lab1CPP_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_3.txt)
set_property(TEST Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "unique: 0 999 1\\.")

add_test(NAME Task2_Test4 COMMAND Lab1CPP_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input2_4.txt)
set_property(TEST Task2_Test4 PROPERTY PASS_REGULAR_EXPRESSION "invalid input data")