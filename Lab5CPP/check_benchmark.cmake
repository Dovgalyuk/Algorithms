execute_process(
    COMMAND "${PROGRAM}" "${INPUT}" "${OUTPUT}" 3
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Benchmark failed: ${error}")
endif()
file(STRINGS "${OUTPUT}" lines)
list(LENGTH lines count)
if(NOT count EQUAL 2)
    message(FATAL_ERROR "Expected a header and one measurement")
endif()
list(GET lines 0 header)
list(GET lines 1 measurement)
if(NOT header STREQUAL "count,avl_ms,set_ms,unordered_set_ms")
    message(FATAL_ERROR "Invalid CSV header")
endif()
if(NOT measurement MATCHES "^10,[0-9]+\\.[0-9]+,[0-9]+\\.[0-9]+,[0-9]+\\.[0-9]+$")
    message(FATAL_ERROR "Invalid measurement: ${measurement}")
endif()
