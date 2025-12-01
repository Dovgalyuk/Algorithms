add_test(NAME Test1
    COMMAND Lab2
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_script.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt
)


add_custom_command(
    OUTPUT test1_output.txt
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test1_script.txt ${CMAKE_CURRENT_SOURCE_DIR}/test1_input.txt > test1_output.txt
)

#add_custom_target(test1_run DEPENDS test1_output.txt)

#add_test(NAME Test1Verify
#    COMMAND ${CMAKE_COMMAND} -E compare_files
#        test1_output.txt
#        ${CMAKE_CURRENT_SOURCE_DIR}/expected_output.txt
#)