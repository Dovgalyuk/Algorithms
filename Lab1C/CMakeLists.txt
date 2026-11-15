add_executable(Lab1C task1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

# 1
add_test(NAME Test1_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Test1_task PROPERTY PASS_REGULAR_EXPRESSION "^Start City1 City2 End")

# 2
add_test(NAME Test2_task COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2_task PROPERTY PASS_REGULAR_EXPRESSION "^A B C E")

# -1 Нет пути
add_test(NAME Test_Neg_NoPath COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_neg1.txt)
set_property(TEST Test_Neg_NoPath PROPERTY PASS_REGULAR_EXPRESSION "^No path")

# -2 Изолированные города
add_test(NAME Test_Neg_Isolated COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_neg2.txt)
set_property(TEST Test_Neg_Isolated PROPERTY PASS_REGULAR_EXPRESSION "^No path")

# -3 Пустой файл
add_test(NAME Test_Neg_Empty COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_neg3.txt)
set_property(TEST Test_Neg_Empty PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")

# -4 Одна строка
add_test(NAME Test_Neg_OneLine COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input_neg4.txt)
set_property(TEST Test_Neg_OneLine PROPERTY PASS_REGULAR_EXPRESSION "^No path")

# -5 Не передан файл
add_test(NAME Test_Neg_NoArgs COMMAND Lab1C)
set_property(TEST Test_Neg_NoArgs PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")

# -6 Файл не существует
add_test(NAME Test_Neg_FileNotFound COMMAND Lab1C "non_existent.txt")
set_property(TEST Test_Neg_FileNotFound PROPERTY PASS_REGULAR_EXPRESSION "^ERROR")