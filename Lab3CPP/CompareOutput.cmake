
if(NOT EXISTS "${INPUT}")
    message(FATAL_ERROR "Input file does not exist: ${INPUT}")
endif()

if(NOT EXISTS "${EXPECTED}")
    message(FATAL_ERROR "Expected output does not exist: ${EXPECTED}")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE error
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR
        "Program returned error code: ${result}\n${error}"
    )
endif()

file(READ "${EXPECTED}" expected)

# Приводим окончания строк к единому формату
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT actual STREQUAL expected)
    message(FATAL_ERROR
        "Output mismatch!\n\n"
        "Expected:\n${expected}\n"
        "Actual:\n${actual}"
    )
endif()

message(STATUS "Output matches expected result")
