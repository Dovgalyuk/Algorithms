execute_process(
COMMAND "${PROGRAM}" "${INPUT}" "${OUTPUT}"
RESULT_VARIABLE result
ERROR_VARIABLE error_output
)

if(NOT "${result}" STREQUAL "0")
message(FATAL_ERROR
"Program failed: ${result}\n${error_output}"
)
endif()

file(READ "${OUTPUT}" actual)
file(READ "${EXPECTED}" expected)

string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT "${actual}" STREQUAL "${expected}")
message(FATAL_ERROR
"Output differs.\nExpected:\n${expected}\nActual:\n${actual}"
)
endif()

