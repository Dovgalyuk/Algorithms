cmake_minimum_required(VERSION 3.10)
project(1Lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# --- сборка ---
add_executable(test_array src/main.cpp)
add_executable(task1      src/task1.cpp)
add_executable(task2      src/task2.cpp)

# --- тесты ---
enable_testing()

# 1. Тест контейнера — только код возврата
add_test(NAME test_array COMMAND test_array)

# 2. Функция: запускает программу, сохраняет вывод, сравнивает с эталоном
function(add_output_test name program input expected)
    set(out ${CMAKE_CURRENT_BINARY_DIR}/${name}_out.txt)

    # Шаг 1: запустить программу и сохранить вывод в файл
    add_test(NAME ${name}_run
        COMMAND sh -c "$<TARGET_FILE:${program}> ${CMAKE_CURRENT_SOURCE_DIR}/tests/${input} > ${out}"
    )

    # Шаг 2: сравнить полученный вывод с эталоном
    add_test(NAME ${name}
        COMMAND ${CMAKE_COMMAND} -E compare_files
            ${out}
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/${expected}
    )

    # Шаг 2 выполняется только после шага 1
    set_tests_properties(${name} PROPERTIES DEPENDS ${name}_run)
endfunction()

# --- task1 ---
add_output_test(task1_test1 task1 task1_input1.txt task1_expected1.txt)
add_output_test(task1_test2 task1 task1_input2.txt task1_expected2.txt)
add_output_test(task1_test3 task1 task1_input3.txt task1_expected3.txt)

# --- task2 ---
add_output_test(task2_test1 task2 task2_input1.txt task2_expected1.txt)
add_output_test(task2_test2 task2 task2_input2.txt task2_expected2.txt)
add_output_test(task2_test3 task2 task2_input3.txt task2_expected3.txt)