
if(NOT EXISTS "${INPUT}")
    message(FATAL_ERROR "Input file not found")
endif()

execute_process(
    COMMAND "${PROGRAM}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE actual
    ERROR_VARIABLE errors
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Program error: ${errors}")
endif()

file(READ "${EXPECTED}" expected)

string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")

string(REGEX REPLACE "\n+$" "" actual "${actual}")
string(REGEX REPLACE "\n+$" "" expected "${expected}")

if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR
        "Wrong answer!\nExpected:\n${expected}\nActual:\n${actual}"
    )
endif()

message(STATUS "Test passed")
