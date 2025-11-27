add_executable(BeatnikC beatnik.c)

target_include_directories(BeatnikC PUBLIC ../LibraryC)
add_dependencies(BeatnikC LibraryC)
target_link_libraries(BeatnikC LibraryC)

add_test(NAME BeatnikSample COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikSample PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME BeatnikNoOp COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/noop_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikNoOp PROPERTY PASS_REGULAR_EXPRESSION "^[\\s]*$")

add_test(NAME BeatnikPushPopSequence COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/push_pop_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikPushPopSequence PROPERTY PASS_REGULAR_EXPRESSION "H")

add_test(NAME BeatnikEmptyScript COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/empty_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikEmptyScript PROPERTY PASS_REGULAR_EXPRESSION "^[\\s]*$")

add_test(NAME BeatnikOutputWithoutPush COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/output_without_push_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikOutputWithoutPush PROPERTY PASS_REGULAR_EXPRESSION "^[\\s]*$")

add_test(NAME BeatnikPushDoubleOutput COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/push_double_output_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikPushDoubleOutput PROPERTY PASS_REGULAR_EXPRESSION "J")

add_test(NAME BeatnikInputEOF COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/input_eof_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/empty_input.txt)
set_property(TEST BeatnikInputEOF PROPERTY PASS_REGULAR_EXPRESSION "J")

add_test(NAME BeatnikEarlyTerminate COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/early_terminate_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/sample_input.txt)
set_property(TEST BeatnikEarlyTerminate PROPERTY PASS_REGULAR_EXPRESSION "J")

add_test(NAME BeatnikAddition COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/addition_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/addition_input.txt)
set_property(TEST BeatnikAddition PROPERTY PASS_REGULAR_EXPRESSION ".")

add_test(NAME BeatnikSubtraction COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/subtraction_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/subtraction_input.txt)
set_property(TEST BeatnikSubtraction PROPERTY PASS_REGULAR_EXPRESSION "^[\\s\\x00]*$")

add_test(NAME BeatnikMultiplication COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/multiplication_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/multiplication_input.txt)
set_property(TEST BeatnikMultiplication PROPERTY PASS_REGULAR_EXPRESSION "d")

add_test(NAME BeatnikDivision COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/division_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/division_input.txt)
set_property(TEST BeatnikDivision PROPERTY PASS_REGULAR_EXPRESSION "^[\\s\\x00]*$")

add_test(NAME BeatnikModulo COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/modulo_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/modulo_input.txt)
set_property(TEST BeatnikModulo PROPERTY PASS_REGULAR_EXPRESSION "J")

add_test(NAME BeatnikInputNumber COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/input_number_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/input_number_input.txt)
set_property(TEST BeatnikInputNumber PROPERTY PASS_REGULAR_EXPRESSION "A")

add_test(NAME BeatnikOutputNumber COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/output_number_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/output_number_input.txt)
set_property(TEST BeatnikOutputNumber PROPERTY PASS_REGULAR_EXPRESSION "74")

add_test(NAME BeatnikConditionalSkipZero COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/conditional_skip_zero_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/conditional_skip_input.txt)
set_property(TEST BeatnikConditionalSkipZero PROPERTY PASS_REGULAR_EXPRESSION "^[\\s\\x00]*$")

add_test(NAME BeatnikConditionalSkipNonZero COMMAND BeatnikC ${CMAKE_CURRENT_SOURCE_DIR}/resources/conditional_skip_nonzero_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/resources/conditional_skip_input.txt)
set_property(TEST BeatnikConditionalSkipNonZero PROPERTY PASS_REGULAR_EXPRESSION "J")

