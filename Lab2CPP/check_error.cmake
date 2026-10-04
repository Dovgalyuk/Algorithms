execute_process(
    COMMAND "${PROGRAM}" "${INPUT}"
    RESULT_VARIABLE code
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
    ERROR_STRIP_TRAILING_WHITESPACE
    ENCODING UTF-8
)

if(NOT "${code}" STREQUAL "1" OR
   NOT "${output}" STREQUAL "" OR
   NOT "${error}" STREQUAL "Ошибка в выражении")
    message(FATAL_ERROR "Unexpected result: exit code '${code}', stdout '${output}', stderr '${error}'")
endif()
