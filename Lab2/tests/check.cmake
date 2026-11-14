execute_process(
    COMMAND "${VM}" "${INPUT}"
    RESULT_VARIABLE code
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
)

if(EXPECTED MATCHES "\\.err$")
    if(NOT "${code}" STREQUAL "1")
        message(FATAL_ERROR
            "Expected exit code 1.\nExit: ${code}\nOutput: ${output}\nError: ${error_output}")
    endif()

    file(READ "${EXPECTED}" expected_error)

    string(STRIP "${error_output}" error_output)
    string(STRIP "${expected_error}" expected_error)

    if(NOT "${error_output}" STREQUAL "${expected_error}")
        message(FATAL_ERROR
            "Error output mismatch.\nExpected:\n${expected_error}\nActual:\n${error_output}")
    endif()
else()
    if(NOT "${code}" STREQUAL "0")
        message(FATAL_ERROR
            "VM failed.\nExit: ${code}\nOutput: ${output}\nError: ${error_output}")
    endif()

    file(READ "${EXPECTED}" expected)

    if(NOT "${output}" STREQUAL "${expected}")
        message(FATAL_ERROR
            "Output mismatch.\nExpected:\n${expected}\nActual:\n${output}")
    endif()
endif()