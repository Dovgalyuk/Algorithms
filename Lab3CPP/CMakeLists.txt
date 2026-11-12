add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

# пример из задания
add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3CPP PROPERTY PASS_REGULAR_EXPRESSION "^9\n######\n#xxxx#\n#x####\n#xxxx#\n######\n$")

# X в углу
add_test(NAME TestLab3CPP_2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3CPP_2 PROPERTY PASS_REGULAR_EXPRESSION "^10\nxxxx\nx##x\nxxxx\n$")

# X окружён стенами
add_test(NAME TestLab3CPP_3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3CPP_3 PROPERTY PASS_REGULAR_EXPRESSION "^1\n\\.\\.\\.\\.\\.\n\\.###\\.\n\\.#x#\\.\n\\.###\\.\n\\.\\.\\.\\.\\.\n$")

# лабиринт без стен
add_test(NAME TestLab3CPP_4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3CPP_4 PROPERTY PASS_REGULAR_EXPRESSION "^12\nxxxx\nxxxx\nxxxx\n$")

# одна строка
add_test(NAME TestLab3CPP_5 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab3CPP_5 PROPERTY PASS_REGULAR_EXPRESSION "^4\n\\.\\.#xxxx#\\.\n$")

# один столбец
add_test(NAME TestLab3CPP_6 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST TestLab3CPP_6 PROPERTY PASS_REGULAR_EXPRESSION "^3\nx\nx\nx\n#\n\\.\n$")

# недостижимая область
add_test(NAME TestLab3CPP_7 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST TestLab3CPP_7 PROPERTY PASS_REGULAR_EXPRESSION "^8\n#########\n#xxx#\\.\\.\\.#\n#x#x#\\.#\\.#\n#xxx#\\.\\.\\.#\n#########\n$")

# большой извилистый лабиринт
add_test(NAME TestLab3CPP_8 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST TestLab3CPP_8 PROPERTY PASS_REGULAR_EXPRESSION "^69\n###############\n#xxxxx#xxxxxxx#\n#####x#x#####x#\n#xxxxx#x#xxx#x#\n#x#####x#x#x#x#\n#x#xxxxx#x#xxx#\n#x#x#######x###\n#xxx#xxxxx#xxx#\n#####x###x###x#\n#xxxxx#xxxxxxx#\n###############\n$")
