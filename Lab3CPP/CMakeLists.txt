add_executable(Lab3CPP_path lab3.cpp)
target_include_directories(Lab3CPP_path PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP_path LibraryCPP)

#пример из задания
add_test(NAME Path_Test1 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST Path_Test1 PROPERTY PASS_REGULAR_EXPRESSION "^2[\r\n]*$")

#прямое ребро 1 -> 3
add_test(NAME Path_Test2 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Path_Test2 PROPERTY PASS_REGULAR_EXPRESSION "^1[\r\n]*$")

# длинная цепочка из 5 вершин
add_test(NAME Path_Test3 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Path_Test3 PROPERTY PASS_REGULAR_EXPRESSION "^4[\r\n]*$")

#выбор кратчайшего из альтернативных путей
add_test(NAME Path_Test4 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Path_Test4 PROPERTY PASS_REGULAR_EXPRESSION "^2[\r\n]*$")

#рёбра ориентированы только в обратную сторону
add_test(NAME Path_Test5 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST Path_Test5 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

#две изолированные компоненты связности
add_test(NAME Path_Test6 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST Path_Test6 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

#пустой граф без рёбер
add_test(NAME Path_Test7 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST Path_Test7 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

#начальная вершина совпадает с конечной
add_test(NAME Path_Test8 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST Path_Test8 PROPERTY PASS_REGULAR_EXPRESSION "^0[\r\n]*$")

#граф из одной вершины
add_test(NAME Path_Test9 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input9.txt)
set_property(TEST Path_Test9 PROPERTY PASS_REGULAR_EXPRESSION "^0[\r\n]*$")

#номер вершины вне допустимого диапазона
add_test(NAME Path_Test10 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input10.txt)
set_property(TEST Path_Test10 PROPERTY PASS_REGULAR_EXPRESSION "IMPOSSIBLE")

#несуществующий входной файл
add_test(NAME Path_Test11 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/missing.txt)
set_property(TEST Path_Test11 PROPERTY PASS_REGULAR_EXPRESSION "cannot open file")

#встреча в узле-мосте
add_test(NAME Path_Test12 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input11.txt)
set_property(TEST Path_Test12 PROPERTY PASS_REGULAR_EXPRESSION "^4[\r\n]*$")

# граф с циклической ловушкой и параллельным коротким путём
add_test(NAME Path_Test13 COMMAND Lab3CPP_path ${CMAKE_CURRENT_SOURCE_DIR}/input12.txt)
set_property(TEST Path_Test13 PROPERTY PASS_REGULAR_EXPRESSION "^2[\r\n]*$")
