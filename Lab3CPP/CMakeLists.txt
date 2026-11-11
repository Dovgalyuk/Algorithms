cmake_minimum_required(VERSION 3.12)
project(Lab3CPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3CPP main.cpp Himbeere.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

enable_testing()

function(add_path_test TEST_NAME INPUT_FILE EXPECTED_FILE)
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${CMAKE_COMMAND}
            -DEXEC=$<TARGET_FILE:Lab3CPP>
            -DINPUT=${INPUT_FILE}
            -DEXPECTED=${EXPECTED_FILE}
            -P "${CMAKE_CURRENT_SOURCE_DIR}/RunTest.cmake"
    )
endfunction()

function(add_nopath_test TEST_NAME INPUT_FILE)
    add_test(
        NAME ${TEST_NAME}
        COMMAND Lab3CPP "${INPUT_FILE}"
    )
    set_tests_properties(${TEST_NAME} PROPERTIES
        PASS_REGULAR_EXPRESSION "No path"
    )
endfunction()

foreach(N RANGE 1 10)
    add_path_test(Test${N}
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test${N}.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test${N}.out")
endforeach()