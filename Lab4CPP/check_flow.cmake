execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE code
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
    ENCODING UTF-8
)

file(READ "${EXPECTED}" expected)
string(REPLACE "\r\n" "\n" output "${output}")
string(REPLACE "\r\n" "\n" expected "${expected}")

if(NOT "${code}" STREQUAL "${EXPECTED_CODE}")
    message(FATAL_ERROR "Unexpected exit code: ${code}\n${error}")
endif()

if(NOT "${output}" STREQUAL "${expected}")
    message(FATAL_ERROR "Unexpected output:\n${output}\nExpected:\n${expected}")
endif()

if(EXPECTED_CODE EQUAL 0)
    if(NOT "${error}" STREQUAL "")
        message(FATAL_ERROR "Unexpected error: ${error}")
    endif()
elseif(NOT "${error}" MATCHES "^Ошибка: ")
    message(FATAL_ERROR "Missing error message: ${error}")
endif()
