add_executable(Lab2CPP task3.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

# Пример 1: обычный случай
add_test(NAME TestLab2CPP_1 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt out1.txt)
add_test(NAME TestLab2CPP_1_ok COMMAND ${CMAKE_COMMAND} -E compare_files out1.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid1.txt)
set_tests_properties(TestLab2CPP_1_ok PROPERTIES DEPENDS TestLab2CPP_1)

# Пример 2: только один элемент больше среднего
add_test(NAME TestLab2CPP_2 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt out2.txt)
add_test(NAME TestLab2CPP_2_ok COMMAND ${CMAKE_COMMAND} -E compare_files out2.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid2.txt)
set_tests_properties(TestLab2CPP_2_ok PROPERTIES DEPENDS TestLab2CPP_2)

# Пример 3: все элементы равны, подходящих элементов нет
add_test(NAME TestLab2CPP_3 COMMAND Lab2CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt out3.txt)
add_test(NAME TestLab2CPP_3_ok COMMAND ${CMAKE_COMMAND} -E compare_files out3.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid3.txt)
set_tests_properties(TestLab2CPP_3_ok PROPERTIES DEPENDS TestLab2CPP_3)
