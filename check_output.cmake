execute_process(
    COMMAND ${PROGRAM} ${INPUT}
    OUTPUT_VARIABLE OUTPUT
)


file(READ ${EXPECTED} EXPECTED_OUTPUT)


if(NOT OUTPUT STREQUAL EXPECTED_OUTPUT)

    message(FATAL_ERROR
    "Неверный результат.\nОжидалось:\n${EXPECTED_OUTPUT}\nПолучено:\n${OUTPUT}"
    )

endif()
