if(CMAKE_SCRIPT_MODE_FILE)
    execute_process(
            COMMAND ${EXE}
            INPUT_FILE ${IN}
            OUTPUT_VARIABLE OUT
            RESULT_VARIABLE RES)

    if(EXPECT_FAIL)
        if(RES EQUAL 0)
            message(FATAL_ERROR "program should have failed, but exited with code 0")
        endif()
    else()
        if(NOT RES EQUAL 0)
            message(FATAL_ERROR "program exited with code ${RES}")
        endif()

        file(READ ${EXPECTED} EXP)
        string(REPLACE "\r\n" "\n" OUT "${OUT}")
        string(REPLACE "\r\n" "\n" EXP "${EXP}")
        string(STRIP "${OUT}" OUT)
        string(STRIP "${EXP}" EXP)
        if(NOT OUT STREQUAL EXP)
            message(FATAL_ERROR "output mismatch\n--- got ---\n${OUT}\n--- expected ---\n${EXP}")
        endif()
    endif()
    return()
endif()


add_executable(floyd main.cpp)
target_include_directories(floyd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPTemplate)

function(add_floyd_test n)
    cmake_parse_arguments(ARG "EXPECT_FAIL" "" "" ${ARGN})

    set(args
            -DEXE=$<TARGET_FILE:floyd>
            -DIN=${CMAKE_CURRENT_SOURCE_DIR}/Tests/input_${n}.txt)
    if(ARG_EXPECT_FAIL)
        list(APPEND args -DEXPECT_FAIL=1)
    else()
        list(APPEND args -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/Tests/expected_${n}.txt)
    endif()


    add_test(NAME floyd_${n}
            COMMAND ${CMAKE_COMMAND} ${args} -P ${CMAKE_CURRENT_LIST_FILE})
endfunction()

foreach(n RANGE 1 17)
    add_floyd_test(${n})
endforeach()

foreach(n RANGE 18 21)
    add_floyd_test(${n} EXPECT_FAIL)
endforeach()