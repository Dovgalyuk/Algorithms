# Тест 1: оригинальный пример — "Hello, aunts!..." → "H"
add_test(NAME BeatnikOriginal
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt
)

# Тест 2: проверка вывода через сравнение файлов
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/output1.txt
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt
        > ${CMAKE_CURRENT_BINARY_DIR}/output1.txt
    DEPENDS Lab2
    VERBATIM
)

add_custom_target(verify_output1 ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/output1.txt)

add_test(NAME BeatnikOriginalVerify
    COMMAND ${CMAKE_COMMAND} -E compare_files
        ${CMAKE_CURRENT_BINARY_DIR}/output1.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/expected_output.txt
)

# Тест 3: простой — команда <5 → завершение без ошибки
add_test(NAME BeatnikStop
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/empty.txt
)   