cmake_minimum_required(VERSION 3.14)
project(Beatnik)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к заголовочным файлам из LibraryCPPtemplate

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ../LibraryCPPTemplate)
target_link_libraries(${PROJECT_NAME} LibraryCPPTemplate)

# Для тестов
enable_testing()

# Простой тест (запуск)
add_test(NAME Test1
    COMMAND beatnik
        ${CMAKE_SOURCE_DIR}/tests/test1_script.txt
        ${CMAKE_SOURCE_DIR}/tests/test1_input.txt
)

# Опционально: тест на вывод
add_custom_command(
    OUTPUT test1_output.txt
    COMMAND beatnik ${CMAKE_SOURCE_DIR}/tests/test1_script.txt ${CMAKE_SOURCE_DIR}/tests/test1_input.txt > test1_output.txt
    VERBATIM
)

add_custom_target(test1_run DEPENDS test1_output.txt)

add_test(NAME Test1Verify
    COMMAND ${CMAKE_COMMAND} -E compare_files
        test1_output.txt
        ${CMAKE_SOURCE_DIR}/tests/expected_output.txt
)