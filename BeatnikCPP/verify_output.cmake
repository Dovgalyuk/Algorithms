execute_process(
    COMMAND "${PROGRAM}" "${SCRIPT}" "${INPUT}"
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error_output)

if(NOT "${exit_code}" STREQUAL "0")
    message(FATAL_ERROR "Beatnik exited with ${exit_code}: ${error_output}")
endif()

if(NOT "${actual}" STREQUAL "${EXPECTED}")
    message(FATAL_ERROR "Expected output [${EXPECTED}], got [${actual}]")
endif()