if(NOT DEFINED PROGRAM)
    message(FATAL_ERROR "PROGRAM is not defined")
endif()
if(NOT DEFINED INPUT_FILE)
    message(FATAL_ERROR "INPUT_FILE is not defined")
endif()
if(NOT DEFINED EXPECTED_FILE)
    message(FATAL_ERROR "EXPECTED_FILE is not defined")
endif()
if(NOT DEFINED TESTNAME)
    message(FATAL_ERROR "TESTNAME is not defined")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${INPUT_FILE}"
    OUTPUT_VARIABLE actual_output
    ERROR_VARIABLE actual_error
    RESULT_VARIABLE exit_code
)

if(NOT exit_code EQUAL 0)
    message(FATAL_ERROR "[${TESTNAME}] program exited with code ${exit_code}\nstderr:\n${actual_error}")
endif()

file(READ "${EXPECTED_FILE}" expected_output)

string(REPLACE "\r\n" "\n" actual_output "${actual_output}")
string(REPLACE "\r\n" "\n" expected_output "${expected_output}")
string(STRIP "${actual_output}" actual_output)
string(STRIP "${expected_output}" expected_output)

if(NOT actual_output STREQUAL expected_output)
    message(FATAL_ERROR
        "[${TESTNAME}] output mismatch\n"
        "--- expected ---\n${expected_output}\n"
        "--- actual ---\n${actual_output}\n")
endif()

message(STATUS "[${TESTNAME}] OK")