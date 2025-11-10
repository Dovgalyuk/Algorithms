add_executable(lab3cppclass Lab32Struct.cpp)
target_include_directories(lab3cppclass PUBLIC ../LibraryCPPClass)
target_link_libraries(lab3cppclass LibraryCPPClass)

set(EXPECTED_OUTPUT "312456780
312450786
310452786
301452786
031452786
431052786
431502786
401532786
410532786
412530786
412503786
412053786
012453786
102453786
120453786
123450786
123456780
")

# Создаем файл с ожидаемым выводом
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt "${EXPECTED_OUTPUT}")

add_test(NAME TestLab31CPPClass COMMAND lab3cppclass 312456780 ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)

# Тест 2: Сравнение файлов
add_test(NAME TestLab3CPPClass_Compare
COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/output.txt ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt)