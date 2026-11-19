add_executable(odds odds.cpp tools.cpp)
target_include_directories(odds PUBLIC ../LibraryCPP)
target_link_libraries(odds LibraryCPP)

add_executable(mode mode.cpp tools.cpp)
target_include_directories(mode PUBLIC ../LibraryCPP)
target_link_libraries(mode LibraryCPP)

add_test(NAME odds_four_seq
    COMMAND odds ${CMAKE_CURRENT_SOURCE_DIR}/tests/odds_four_seq.txt)
set_property(TEST odds_four_seq PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME odds_all_odd
    COMMAND odds ${CMAKE_CURRENT_SOURCE_DIR}/tests/odds_all_odd.txt)
set_property(TEST odds_all_odd PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME odds_all_even
    COMMAND odds ${CMAKE_CURRENT_SOURCE_DIR}/tests/odds_all_even.txt)
set_property(TEST odds_all_even PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME odds_all_negative
    COMMAND odds ${CMAKE_CURRENT_SOURCE_DIR}/tests/odds_all_negative.txt)
set_property(TEST odds_all_negative PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME odds_single
    COMMAND odds ${CMAKE_CURRENT_SOURCE_DIR}/tests/odds_single.txt)
set_property(TEST odds_single PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME mode_2
    COMMAND mode ${CMAKE_CURRENT_SOURCE_DIR}/tests/mode_2.txt)
set_property(TEST mode_2 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME mode_equal
    COMMAND mode ${CMAKE_CURRENT_SOURCE_DIR}/tests/mode_equal.txt)
set_property(TEST mode_equal PROPERTY PASS_REGULAR_EXPRESSION "7")

add_test(NAME mode_unique
    COMMAND mode ${CMAKE_CURRENT_SOURCE_DIR}/tests/mode_unique.txt)
set_property(TEST mode_unique PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME mode_max
    COMMAND mode ${CMAKE_CURRENT_SOURCE_DIR}/tests/mode_max.txt)
set_property(TEST mode_max PROPERTY PASS_REGULAR_EXPRESSION "1000")