add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

# Тест 1: Пример из задания (ромб 7 строк)
add_test(NAME Lab3Test1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt output1.txt)
set_property(TEST Lab3Test1 PROPERTY PASS_REGULAR_EXPRESSION "      3\n    # 2 5\n  # # 1 4 1\n3 2 # 2 3 2 3\n  1 2 3 4 1\n    3 4 5\n      5")
add_test(NAME Lab3Test1_check COMMAND ${CMAKE_COMMAND} -E compare_files output1.txt ${CMAKE_CURRENT_SOURCE_DIR}/Test/output1.txt)

# Тест 2: Лабиринт 5 строк с изолированными углами
add_test(NAME Lab3Test2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt output2.txt)
add_test(NAME Lab3Test2_check COMMAND ${CMAKE_COMMAND} -E compare_files output2.txt ${CMAKE_CURRENT_SOURCE_DIR}/Test/output2.txt)

# Тест 3: Лабиринт со сложными тупиками и барьерами
add_test(NAME Lab3Test3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt output3.txt)
add_test(NAME Lab3Test3_check COMMAND ${CMAKE_COMMAND} -E compare_files output3.txt ${CMAKE_CURRENT_SOURCE_DIR}/Test/output3.txt)

# Тест 4: Небольшой лабиринт 3 строки
add_test(NAME Lab3Test4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Test/input4.txt output4.txt)
add_test(NAME Lab3Test4_check COMMAND ${CMAKE_COMMAND} -E compare_files output4.txt ${CMAKE_CURRENT_SOURCE_DIR}/Test/output4.txt)
