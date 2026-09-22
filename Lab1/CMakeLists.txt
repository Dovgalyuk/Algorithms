add_executable(Fastest fastest.cpp)

target_include_directories(
    Fastest
    PUBLIC
    ../LibraryCPPTemplate
)


add_executable(MaxFiveSum max_five_sum.cpp)

target_include_directories(
    MaxFiveSum
    PUBLIC
    ../LibraryCPPTemplate
)


add_test(
    NAME FastestTest1
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:Fastest>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_1.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/fastest_1.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)


add_test(
    NAME FastestTest2
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:Fastest>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_2.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/fastest_2.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)


add_test(
    NAME FastestTest3
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:Fastest>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_3.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/fastest_3.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)


add_test(
    NAME MaxFiveSumTest1
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:MaxFiveSum>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/sum_1.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/sum_1.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)


add_test(
    NAME MaxFiveSumTest2
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:MaxFiveSum>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/sum_2.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/sum_2.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)


add_test(
    NAME MaxFiveSumTest3
    COMMAND ${CMAKE_COMMAND}
    -DPROGRAM=$<TARGET_FILE:MaxFiveSum>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/input/sum_3.txt
    -DEXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/expected/sum_3.txt
    -P ${CMAKE_SOURCE_DIR}/check_output.cmake
)
