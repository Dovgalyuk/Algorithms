add_executable(Lab1CPP Array.cpp)
target_include_directories(Lab1CPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lab1CPP LibraryCPP)


add_test(NAME TestLab1CPP_input_task1
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP_input_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 4.5")

add_test(NAME TestLab1CPP_input_task2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1CPP_input_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 0")


add_test(NAME TestLab1CPP_test1_task1
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestLab1CPP_test1_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 4.5")

add_test(NAME TestLab1CPP_test1_task2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test1.txt)
set_property(TEST TestLab1CPP_test1_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 0")


add_test(NAME TestLab1CPP_test2_task1
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestLab1CPP_test2_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 3.25")

add_test(NAME TestLab1CPP_test2_task2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt)
set_property(TEST TestLab1CPP_test2_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 5")


add_test(NAME TestLab1CPP_test3_task1
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestLab1CPP_test3_task1 PROPERTY
    PASS_REGULAR_EXPRESSION "Average: 2.5")

add_test(NAME TestLab1CPP_test3_task2
         COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/test3.txt)
set_property(TEST TestLab1CPP_test3_task2 PROPERTY
    PASS_REGULAR_EXPRESSION "Most frequent element: 1")