add_test(
    NAME Lab3CPPClass_Test_1
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test1.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test1-expected.txt
            -DTESTNAME=test1
            -DPROGRAM=$<TARGET_FILE:Lab3CPPClass>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPPClass_Test_2
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test2-expected.txt
            -DTESTNAME=test2
            -DPROGRAM=$<TARGET_FILE:Lab3CPPClass>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)
