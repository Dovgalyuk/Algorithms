add_test(
    NAME Lab3CPP_Test
    COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/input.txt
            -DOUTPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/output.txt
            -DPROGRAM=$<TARGET_FILE:Lab3CPP>
            -P ${CMAKE_CURRENT_SOURCE_DIR}/run_game_eight_test.cmake
)