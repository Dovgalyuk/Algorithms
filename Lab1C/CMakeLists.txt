add_executable(Task1CPP task1.cpp)
target_include_directories(Task1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Task1CPP LibraryCPP)

add_executable(Task2CPP task2.cpp)
target_include_directories(Task2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Task2CPP LibraryCPP)


add_test(
    NAME TestTask1_1
    COMMAND Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/task1_1.txt
)
set_property(
    TEST TestTask1_1
    PROPERTY PASS_REGULAR_EXPRESSION "4 0 2 3 4"
)


add_test(
    NAME TestTask1_2
    COMMAND Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/task1_2.txt
)
set_property(
    TEST TestTask1_2
    PROPERTY PASS_REGULAR_EXPRESSION "0"
)


add_test(
    NAME TestTask1_3
    COMMAND Task1CPP ${CMAKE_CURRENT_SOURCE_DIR}/task1_3.txt
)
set_property(
    TEST TestTask1_3
    PROPERTY PASS_REGULAR_EXPRESSION "3 0 1 2"
)


add_test(
    NAME TestTask2_1
    COMMAND Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/task2_1.txt
)
set_property(
    TEST TestTask2_1
    PROPERTY PASS_REGULAR_EXPRESSION "1 2"
)


add_test(
    NAME TestTask2_2
    COMMAND Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/task2_2.txt
)
set_property(
    TEST TestTask2_2
    PROPERTY PASS_REGULAR_EXPRESSION "8"
)


add_test(
    NAME TestTask2_3
    COMMAND Task2CPP ${CMAKE_CURRENT_SOURCE_DIR}/task2_3.txt
)
set_property(
    TEST TestTask2_3
    PROPERTY PASS_REGULAR_EXPRESSION "0 1000 7"
)