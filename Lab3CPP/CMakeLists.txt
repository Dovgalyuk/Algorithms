add_executable(KnightPath main.cpp)
target_include_directories(KnightPath PUBLIC ../LibraryCPP)
target_link_libraries(KnightPath LibraryCPP)

set(TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake)
set(TEST_DATA ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_test(NAME knight_1
    COMMAND ${CMAKE_COMMAND}
        "-DPROGRAM=$<TARGET_FILE:KnightPath>"
        "-DINPUT=${TEST_DATA}/knight_1.txt"
        "-DEXPECTED=${TEST_DATA}/knight_1_expected.txt"
        -P ${TEST_SCRIPT})
