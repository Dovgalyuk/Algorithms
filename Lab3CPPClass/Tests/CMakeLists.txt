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

add_test(
    NAME Lab3CPPClass_Test_3
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test3.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test3-expected.txt
            -DTESTNAME=test3
            -DPROGRAM=$<TARGET_FILE:Lab3CPPClass>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPPClass_Test_4
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test4.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test4-expected.txt
            -DTESTNAME=test4
            -DPROGRAM=$<TARGET_FILE:Lab3CPPClass>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPPClass_Test_5
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test5.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test5-expected.txt
            -DTESTNAME=test5
            -DPROGRAM=$<TARGET_FILE:Lab3CPPClass>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)