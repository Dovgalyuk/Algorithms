add_executable(Task1CPP "task1.cpp")
target_include_directories(Task1CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Task1CPP LibraryCPPClass)
add_executable(Task2CPP "task2.cpp")
target_include_directories(Task2CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Task2CPP LibraryCPPClass)

add_test(NAME Test1_Task1CPP COMMAND Task1CPP "${CMAKE_CURRENT_SOURCE_DIR}/T1_test1.txt")
set_property(TEST Test1_Task1CPP PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME Test2_Task1CPP COMMAND Task1CPP "${CMAKE_CURRENT_SOURCE_DIR}/T1_test2.txt")
set_property(TEST Test2_Task1CPP PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME Test3_Task1CPP COMMAND Task1CPP "${CMAKE_CURRENT_SOURCE_DIR}/T1_test3.txt")
set_property(TEST Test3_Task1CPP PROPERTY PASS_REGULAR_EXPRESSION "9")

add_test(NAME Test4_Task1CPP COMMAND Task1CPP "${CMAKE_CURRENT_SOURCE_DIR}/T1_test4.txt")
set_property(TEST Test4_Task1CPP PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Test5_Task1CPP COMMAND Task1CPP "${CMAKE_CURRENT_SOURCE_DIR}/T1_test5.txt")
set_property(TEST Test5_Task1CPP PROPERTY PASS_REGULAR_EXPRESSION "234")


add_test(NAME Test1_Task2CPP COMMAND Task2CPP "${CMAKE_CURRENT_SOURCE_DIR}/T2_test1.txt")
set_property(TEST Test1_Task2CPP PROPERTY PASS_REGULAR_EXPRESSION "2 3")

add_test(NAME Test2_Task2CPP COMMAND Task2CPP "${CMAKE_CURRENT_SOURCE_DIR}/T2_test2.txt")
set_property(TEST Test2_Task2CPP PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME Test3_Task2CPP COMMAND Task2CPP "${CMAKE_CURRENT_SOURCE_DIR}/T2_test3.txt")
set_property(TEST Test3_Task2CPP PROPERTY PASS_REGULAR_EXPRESSION "3 5 7 11 13 17 19")

add_test(NAME Test4_Task2CPP COMMAND Task2CPP "${CMAKE_CURRENT_SOURCE_DIR}/T2_test4.txt")
set_property(TEST Test4_Task2CPP PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME Test5_Task2CPP COMMAND Task2CPP "${CMAKE_CURRENT_SOURCE_DIR}/T2_test5.txt")
set_property(TEST Test5_Task2CPP PROPERTY PASS_REGULAR_EXPRESSION "6 10 15 21 35")