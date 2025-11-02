cmake_minimum_required(VERSION 3.14)
project(Lab2CPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculon
    main.cpp
)

target_link_libraries(calculon PRIVATE LibraryCPP)

target_include_directories(calculon PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)

enable_testing()

# --- Тест 1 ---
add_test(
  NAME calculon_sample
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)

set_tests_properties(calculon_sample PROPERTIES
  PASS_REGULAR_EXPRESSION "72 101 108 108 111 44 32 119 114 108 100 33 10[ \\t\\r\\n]*"
)

# --- Тест 2 ---
add_test(
  NAME calculon_sample_2
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script_2.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input_2.txt
)

set_tests_properties(calculon_sample_2 PROPERTIES
  PASS_REGULAR_EXPRESSION "79 75 10[ \\t\\r\\n]*"
)

# --- Тест 3 ---
add_test(
  NAME calculon_sample_3
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script_3.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input_3.txt
)

set_tests_properties(calculon_sample_3 PROPERTIES
  PASS_REGULAR_EXPRESSION "49 50 51 10[ \\t\\r\\n]*"
)
