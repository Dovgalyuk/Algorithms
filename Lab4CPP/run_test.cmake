set(program ${PROGRAM})
set(input ${INPUT})
set(start ${START})
set(end ${END})
set(output ${OUTPUT})
set(expected ${EXPECTED})

execute_process(
    COMMAND ${program} ${input} ${start} ${end}
    OUTPUT_FILE ${output}
    RESULT_VARIABLE result_code
)

if(NOT result_code EQUAL 0)
    message(FATAL_ERROR "Program failed with exit code ${result_code}")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E compare_files ${expected} ${output}
    RESULT_VARIABLE compare_result
)

if(NOT compare_result EQUAL 0)
    message(STATUS "Expected output:")
    file(READ ${expected} expected_content)
    message(${expected_content})
    
    message(STATUS "Actual output:")
    file(READ ${output} actual_content)
    message(${actual_content})
    
    message(FATAL_ERROR "Test failed: Output differs from expected")
endif()

message("Test passed successfully")