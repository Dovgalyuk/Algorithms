add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3CPP LibraryCPPClass)

add_test(
    NAME Lab3CPP_Test_1
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test1-expected.txt
            -DTESTNAME=test1
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPP_Test_2
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test2-expected.txt
            -DTESTNAME=test2
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPP_Test_3
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test3-expected.txt
            -DTESTNAME=test3
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPP_Test_4
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test4-expected.txt
            -DTESTNAME=test4
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPP_Test_5
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test5-expected.txt
            -DTESTNAME=test5
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)

add_test(
    NAME Lab3CPP_Test_6
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test6.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/tests/test6-expected.txt
            -DTESTNAME=test6
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake
)
