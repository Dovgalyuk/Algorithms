if(NOT DEFINED PROGRAM OR NOT DEFINED INPUT OR NOT DEFINED EXPECTED)
    message(FATAL_ERROR "Required: PROGRAM, INPUT, EXPECTED")
endif()

if(DEFINED MODE AND MODE STREQUAL "arg")
    execute_process(
        COMMAND "${PROGRAM}" "${INPUT}"
        OUTPUT_VARIABLE actual
        ERROR_VARIABLE errors
        RESULT_VARIABLE exit_code
    )
else()
    execute_process(
        COMMAND "${PROGRAM}"
        INPUT_FILE "${INPUT}"
        OUTPUT_VARIABLE actual
        ERROR_VARIABLE errors
        RESULT_VARIABLE exit_code
    )
endif()

if(NOT "${exit_code}" STREQUAL "0")
    message(FATAL_ERROR "Program exited with ${exit_code}: ${errors}")
endif()

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")
if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "Output mismatch for ${INPUT}\nExpected:\n${expected}\nActual:\n${actual}")
endif()
