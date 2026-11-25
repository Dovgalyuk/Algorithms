add_executable(KnightPath main.cpp)
target_include_directories(KnightPath PUBLIC ../LibraryCPP)
target_link_libraries(KnightPath LibraryCPP)

set(TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake)
set(TEST_DATA ${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(SUCCESS_CASES knight_1 knight_direct knight_detour knight_two_paths)
set(FAILURE_CASES knight_blocked_start knight_disconnected knight_missing_exit knight_invalid_row)

foreach(CASE IN LISTS SUCCESS_CASES FAILURE_CASES)
    if(CASE IN_LIST FAILURE_CASES)
        set(EXPECTATION "-DEXPECTED_EXIT=1")
    else()
        set(EXPECTATION "-DEXPECTED=${TEST_DATA}/${CASE}_expected.txt")
        if(CASE STREQUAL "knight_two_paths")
            list(APPEND EXPECTATION "-DEXPECTED_ALTERNATIVE=${TEST_DATA}/${CASE}_alternative.txt")
        endif()
    endif()

    add_test(NAME ${CASE}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:KnightPath>"
            "-DINPUT=${TEST_DATA}/${CASE}.txt"
            ${EXPECTATION}
            -P ${TEST_SCRIPT})
endforeach()
