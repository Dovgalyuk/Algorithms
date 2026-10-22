add_executable(ExpressionToAsm main.cpp)
target_include_directories(ExpressionToAsm PUBLIC ../LibraryCPP)
target_link_libraries(ExpressionToAsm LibraryCPP)

set(TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake)
set(TEST_DATA ${CMAKE_CURRENT_SOURCE_DIR}/tests)

foreach(CASE expr_1 expr_2 expr_3 expr_4 expr_5 expr_6)
    add_test(NAME ${CASE}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:ExpressionToAsm>"
            "-DINPUT=${TEST_DATA}/${CASE}.txt"
            "-DEXPECTED=${TEST_DATA}/${CASE}_expected.txt"
            -P ${TEST_SCRIPT})
endforeach()
