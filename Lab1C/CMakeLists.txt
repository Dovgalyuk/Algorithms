add_executable(Lab1C_task1 task1.c)
target_include_directories(Lab1C_task1 PUBLIC ../LibraryC)
target_link_libraries(Lab1C_task1 LibraryC)

add_executable(Lab1C_task2 task2.c)
target_include_directories(Lab1C_task2 PUBLIC ../LibraryC)
target_link_libraries(Lab1C_task2 LibraryC)

add_test(NAME TestTask1_input
         COMMAND Lab1C_task1 ${CMAKE_CURRENT_SOURCE_DIR}/input_task1.txt)
set_property(TEST TestTask1_input PROPERTY
             PASS_REGULAR_EXPRESSION "Положительные числа: 1 2 3 4 5 6 7 8 9 ")

add_test(NAME TestTask2_input
         COMMAND Lab1C_task2 ${CMAKE_CURRENT_SOURCE_DIR}/input_task2.txt)
set_property(TEST TestTask2_input PROPERTY
             PASS_REGULAR_EXPRESSION "не делятся ни на какой другой элемент: 1 ")
