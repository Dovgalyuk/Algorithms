add_executable(Task1 task1.cpp)
target_include_directories(Task1 PUBLIC ../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_executable(Task2 task2.cpp)
target_include_directories(Task2 PUBLIC ../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

set(TEST_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake)
set(TEST_DATA ${CMAKE_CURRENT_SOURCE_DIR}/tests)

foreach(CASE task1_1 task1_2 task1_3)
    add_test(NAME ${CASE}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Task1>"
            "-DINPUT=${TEST_DATA}/${CASE}.txt"
            "-DEXPECTED=${TEST_DATA}/${CASE}_expected.txt"
            -P ${TEST_SCRIPT})
endforeach()

foreach(CASE task2_1 task2_2 task2_3)
    add_test(NAME ${CASE}
        COMMAND ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:Task2>"
            "-DINPUT=${TEST_DATA}/${CASE}.txt"
            "-DEXPECTED=${TEST_DATA}/${CASE}_expected.txt"
            -P ${TEST_SCRIPT})
endforeach()
