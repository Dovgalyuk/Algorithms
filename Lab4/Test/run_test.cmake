set(program  "${PROGRAM}")
set(input    "${INPUT}")
set(output   "${OUTPUT}")
set(expected "${EXPECTED}")

message("${PROGRAM}")
message("${INPUT}")
message("${OUTPUT}")
message("${EXPECTED}")

execute_process(
        COMMAND "${program}" "${input}" "${output}"
        RESULT_VARIABLE code
)

if(NOT code EQUAL 0)
    message(FATAL_ERROR "Program failed with exit code ${code}")
endif()

execute_process(
        COMMAND "${CMAKE_COMMAND}" -E compare_files "${expected}" "${output}"
        RESULT_VARIABLE cmp
)

if(NOT cmp EQUAL 0)
    message(FATAL_ERROR "Files differ!")
endif()