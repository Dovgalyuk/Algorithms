add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

# В каждом файле два массива: первый для task1, второй для task2.
# Первая строка вывода - результат task1, вторая - task2.

add_test(NAME TestLab1CPP_1 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1CPP_1 PROPERTY PASS_REGULAR_EXPRESSION "^2[\r\n]+1x3 2x2 3x4 1x1[\r\n]*$")

add_test(NAME TestLab1CPP_2 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab1CPP_2 PROPERTY PASS_REGULAR_EXPRESSION "^2 6[\r\n]+1x1 2x1 3x1 4x1 5x1[\r\n]*$")

add_test(NAME TestLab1CPP_3 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab1CPP_3 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]+7x6[\r\n]*$")

add_test(NAME TestLab1CPP_4 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab1CPP_4 PROPERTY PASS_REGULAR_EXPRESSION "^1 4[\r\n]+-1x2 0x3 5x1 -1x2[\r\n]*$")

add_test(NAME TestLab1CPP_5 COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab1CPP_5 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]+$")
