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

# тест 1
add_test(
  NAME calculon_sample
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)
set_tests_properties(calculon_sample PROPERTIES
  PASS_REGULAR_EXPRESSION "72[\\t \\r\\n]+101[\\t \\r\\n]+108[\\t \\r\\n]+108[\\t \\r\\n]+111[\\t \\r\\n]+44[\\t \\r\\n]+32[\\t \\r\\n]+119[\\t \\r\\n]+114[\\t \\r\\n]+108[\\t \\r\\n]+100[\\t \\r\\n]+33[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 2
add_test(
  NAME calculon_sample_2
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script_2.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input_2.txt
)
set_tests_properties(calculon_sample_2 PROPERTIES
  PASS_REGULAR_EXPRESSION "79[\\t \\r\\n]+75[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 3
add_test(
  NAME calculon_sample_3
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_script_3.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input_3.txt
)
set_tests_properties(calculon_sample_3 PROPERTIES
  PASS_REGULAR_EXPRESSION "49[\\t \\r\\n]+50[\\t \\r\\n]+51[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 4
add_test(NAME calculon_loop_simple
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/loop_simple.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)
set_tests_properties(calculon_loop_simple PROPERTIES
  PASS_REGULAR_EXPRESSION ".*65[\\t \\r\\n]+65[\\t \\r\\n]+65[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 5
add_test(NAME calculon_loop_nested
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/loop_nested.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)
set_tests_properties(calculon_loop_nested PROPERTIES
  PASS_REGULAR_EXPRESSION ".*88[\\t \\r\\n]+88[\\t \\r\\n]+88[\\t \\r\\n]+88[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 6
add_test(NAME calculon_arith
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/arith.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)
set_tests_properties(calculon_arith PROPERTIES
  PASS_REGULAR_EXPRESSION ".*7[\\t \\r\\n]+28[\\t \\r\\n]+3[\\t \\r\\n]+10[\\t \\r\\n]*"
)

# тест 7
add_test(NAME calculon_cond
  COMMAND $<TARGET_FILE:calculon>
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/cond.cal
          ${CMAKE_CURRENT_SOURCE_DIR}/tests/sample_input.txt
)
set_tests_properties(calculon_cond PROPERTIES
  PASS_REGULAR_EXPRESSION ".*63[\\t \\r\\n]+10[\\t \\r\\n]*"
)
