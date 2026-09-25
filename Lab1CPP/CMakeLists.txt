add_executable(Lab1CPP_Task1 task1.cpp)
target_include_directories(Lab1CPP_Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task1 LibraryCPP)

add_executable(Lab1CPP_Task2 task2.cpp)
target_include_directories(Lab1CPP_Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP_Task2 LibraryCPP)

add_test(NAME Lab1_Task1_Test1 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test1_1.txt)
set_property(TEST Lab1_Task1_Test1 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME Lab1_Task1_Test2 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test1_2.txt)
set_property(TEST Lab1_Task1_Test2 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Lab1_Task1_Test3 COMMAND Lab1CPP_Task1 ${CMAKE_CURRENT_SOURCE_DIR}/test1_3.txt)
set_property(TEST Lab1_Task1_Test3 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Lab1_Task2_Test1 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test2_1.txt)
set_property(TEST Lab1_Task2_Test1 PROPERTY PASS_REGULAR_EXPRESSION "3 5 7")

add_test(NAME Lab1_Task2_Test2 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test2_2.txt)
set_property(TEST Lab1_Task2_Test2 PROPERTY PASS_REGULAR_EXPRESSION "9")

add_test(NAME Lab1_Task2_Test3 COMMAND Lab1CPP_Task2 ${CMAKE_CURRENT_SOURCE_DIR}/test2_3.txt)
set_property(TEST Lab1_Task2_Test3 PROPERTY PASS_REGULAR_EXPRESSION "3")