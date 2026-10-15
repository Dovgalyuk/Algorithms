set(OUT "${CMAKE_CURRENT_BINARY_DIR}/_actual.txt")

execute_process(
    COMMAND "${EXE}" "${IN}"
    OUTPUT_FILE "${OUT}"
    RESULT_VARIABLE rc
)

if(NOT rc EQUAL 0)
    message(FATAL_ERROR "Program exited with code ${rc}")
endif()

file(READ "${OUT}" actual)
file(READ "${EXPECTED}" expected)

if(NOT actual STREQUAL expected)
    message(FATAL_ERROR
        "Output mismatch.\n"
        "Input:    ${IN}\n"
        "Expected: [${expected}]\n"
        "Actual:   [${actual}]")
endif()