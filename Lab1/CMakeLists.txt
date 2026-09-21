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
    COMMAND Fastest ${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_1.txt
)


add_test(
    NAME FastestTest2
    COMMAND Fastest ${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_2.txt
)


add_test(
    NAME FastestTest3
    COMMAND Fastest ${CMAKE_CURRENT_SOURCE_DIR}/input/fastest_3.txt
)


add_test(
    NAME MaxFiveSumTest1
    COMMAND MaxFiveSum ${CMAKE_CURRENT_SOURCE_DIR}/input/sum_1.txt
)


add_test(
    NAME MaxFiveSumTest2
    COMMAND MaxFiveSum ${CMAKE_CURRENT_SOURCE_DIR}/input/sum_2.txt
)


add_test(
    NAME MaxFiveSumTest3
    COMMAND MaxFiveSum ${CMAKE_CURRENT_SOURCE_DIR}/input/sum_3.txt
)
