execute_process(
    COMMAND ${PROGRAM} ${INPUT_FILE}
    OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME}-actual.txt
    RESULT_VARIABLE res
)
if(NOT res EQUAL 0)
    message(FATAL_ERROR "Program exited with ${res}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E compare_files
            ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME}-actual.txt
            ${OUTPUT_FILE}
    RESULT_VARIABLE diff_res
)
if(NOT diff_res EQUAL 0)
    message(FATAL_ERROR "Output differs from expected")
endif()
