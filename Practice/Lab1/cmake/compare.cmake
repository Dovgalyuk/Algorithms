if(NOT EXISTS "${ACTUAL}")
    message(FATAL_ERROR "Actual file not found: ${ACTUAL}")
endif()

if(NOT EXISTS "${EXPECTED}")
    message(FATAL_ERROR "Expected file not found: ${EXPECTED}")
endif()

file(READ "${ACTUAL}" actual_content)
file(READ "${EXPECTED}" expected_content)

string(STRIP "${actual_content}" actual_stripped)
string(STRIP "${expected_content}" expected_stripped)

if(NOT actual_stripped STREQUAL expected_stripped)
    message(FATAL_ERROR
        "Mismatch!\n--- Expected ---\n${expected_content}\n--- Actual ---\n${actual_content}")
endif()

message(STATUS "Compare OK: ${ACTUAL}")