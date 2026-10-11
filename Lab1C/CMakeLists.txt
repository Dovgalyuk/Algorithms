add_executable(task1 task1.cpp)
target_include_directories(task1 PRIVATE ${CMAKE_SOURCE_DIR}/LibraryCPP)
target_link_libraries(task1 LibraryCPP)


add_test(
    NAME test1_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test1_output.txt
)
add_test(
    NAME test1_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test1_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_expected.txt
)
set_tests_properties(test1_check PROPERTIES DEPENDS test1_run)

add_test(
    NAME test2_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test2_output.txt
)
add_test(
    NAME test2_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test2_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_expected.txt
)
set_tests_properties(test2_check PROPERTIES DEPENDS test2_run)


add_test(
    NAME test3_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test3_output.txt
)
add_test(
    NAME test3_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test3_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3_expected.txt
)
set_tests_properties(test3_check PROPERTIES DEPENDS test3_run)


add_test(
    NAME test4_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test4_output.txt
)
add_test(
    NAME test4_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test4_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4_expected.txt
)
set_tests_properties(test4_check PROPERTIES DEPENDS test4_run)


add_test(
    NAME test5_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test5_output.txt
)
add_test(
    NAME test5_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test5_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5_expected.txt
)
set_tests_properties(test5_check PROPERTIES DEPENDS test5_run)


add_test(
    NAME test6_run
    COMMAND task1
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6_input.txt
            ${CMAKE_CURRENT_BINARY_DIR}/test6_output.txt
)
add_test(
    NAME test6_check
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
            ${CMAKE_CURRENT_BINARY_DIR}/test6_output.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/test6_expected.txt
)
set_tests_properties(test6_check PROPERTIES DEPENDS test6_run)

