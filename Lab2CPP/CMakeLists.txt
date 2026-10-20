add_executable(Lab2CPP_befunge befunge.cpp)
target_include_directories(Lab2CPP_befunge PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP_befunge LibraryCPP)

#примеры из задания
add_test(NAME Befunge_Test COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Befunge_Test PROPERTY PASS_REGULAR_EXPRESSION "^3[\r\n]+2[\r\n]+1[\r\n]*$")

add_test(NAME Befunge_Test2 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Befunge_Test2 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]+2[\r\n]+3[\r\n]+6[\r\n]*$")

#собственные тесты
#вычитание: 9 - 2
add_test(NAME Befunge_Test3 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Befunge_Test3 PROPERTY PASS_REGULAR_EXPRESSION "^7[\r\n]*$")

#деление и остаток: 8 / 2 и 7 % 3
add_test(NAME Befunge_Test4 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Befunge_Test4 PROPERTY PASS_REGULAR_EXPRESSION "^4[\r\n]+1[\r\n]*$")

#логическое не
add_test(NAME Befunge_Test5 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST Befunge_Test5 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]+0[\r\n]*$")

#логическое больше: 5 > 2, 2 > 5, 3 > 3
add_test(NAME Befunge_Test6 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST Befunge_Test6 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]+0[\r\n]+0[\r\n]*$")

#вывод из пустого стека даёт 0
add_test(NAME Befunge_Test7 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST Befunge_Test7 PROPERTY PASS_REGULAR_EXPRESSION "^0[\r\n]*$")

#деление на ноль
add_test(NAME Befunge_Test8 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST Befunge_Test8 PROPERTY PASS_REGULAR_EXPRESSION "division by zero")

#случайное число
add_test(NAME Befunge_Test9 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input9.txt)
set_property(TEST Befunge_Test9 PROPERTY PASS_REGULAR_EXPRESSION "^[0-9][\r\n]*$")

#переполнение
add_test(NAME Befunge_Test10 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/input10.txt)
set_property(TEST Befunge_Test10 PROPERTY PASS_REGULAR_EXPRESSION "overflow")

#файл не найден
add_test(NAME Befunge_Test11 COMMAND Lab2CPP_befunge ${CMAKE_CURRENT_SOURCE_DIR}/missing.txt)
set_property(TEST Befunge_Test11 PROPERTY PASS_REGULAR_EXPRESSION "cannot open file")
