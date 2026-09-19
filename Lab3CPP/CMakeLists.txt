add_executable(Lab3CPP task4.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

# Пример 1: единственное чёткое чаще всего встречающееся число
add_test(NAME TestLab3CPP_1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt out1.txt)
add_test(NAME TestLab3CPP_1_ok COMMAND ${CMAKE_COMMAND} -E compare_files out1.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid1.txt)
set_tests_properties(TestLab3CPP_1_ok PROPERTIES DEPENDS TestLab3CPP_1)

# Пример 2: несколько чисел с одинаковой частотой - выбирается наименьшее
add_test(NAME TestLab3CPP_2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt out2.txt)
add_test(NAME TestLab3CPP_2_ok COMMAND ${CMAKE_COMMAND} -E compare_files out2.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid2.txt)
set_tests_properties(TestLab3CPP_2_ok PROPERTIES DEPENDS TestLab3CPP_2)

# Пример 3: значения на границах диапазона [0, 1000]
add_test(NAME TestLab3CPP_3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt out3.txt)
add_test(NAME TestLab3CPP_3_ok COMMAND ${CMAKE_COMMAND} -E compare_files out3.txt ${CMAKE_CURRENT_SOURCE_DIR}/valid3.txt)
set_tests_properties(TestLab3CPP_3_ok PROPERTIES DEPENDS TestLab3CPP_3)
