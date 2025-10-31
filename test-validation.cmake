# ���� ��� �������� �������� ������ ������
execute_process(
    COMMAND ${TEST_COMMAND}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE ACTUAL_OUTPUT
    RESULT_VARIABLE EXIT_CODE
)

if(NOT EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "���� ���������� � �������: ${EXIT_CODE}")
endif()

# ��������� ������� ���������� ������
if(NOT ACTUAL_OUTPUT MATCHES "${EXPECTED_OUTPUT}")
    message(FATAL_ERROR "���� �� ������: ��������� ����� �� ������.\n���������: ${EXPECTED_OUTPUT}\n��������: ${ACTUAL_OUTPUT}")
else()
    message("���� ������ �������!")
endif()