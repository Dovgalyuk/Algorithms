add_test(
    NAME LabirintTest1
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/first.txt
)
set_tests_properties(LabirintTest1 PROPERTIES PASS_REGULAR_EXPRESSION "4")

add_test(
    NAME LabirintTest2
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/second.txt
)
set_tests_properties(LabirintTest2 PROPERTIES PASS_REGULAR_EXPRESSION "7")

add_test(
    NAME LabirintTest3
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/third.txt
)
set_tests_properties(LabirintTest3 PROPERTIES PASS_REGULAR_EXPRESSION "7")

add_test(
    NAME LabirintTest4
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/fourth.txt
)
set_tests_properties(LabirintTest4 PROPERTIES PASS_REGULAR_EXPRESSION "3")

add_test(
    NAME LabirintTest5
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/fifth.txt
)
set_tests_properties(LabirintTest5 PROPERTIES PASS_REGULAR_EXPRESSION "9")

add_test(
    NAME LabirintTest6
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/sixth.txt
)
set_tests_properties(LabirintTest6 PROPERTIES PASS_REGULAR_EXPRESSION "2")

add_test(
    NAME LabirintTest7
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/seventh.txt
)
set_tests_properties(LabirintTest7 PROPERTIES PASS_REGULAR_EXPRESSION "5")

add_test(
    NAME LabirintTest8
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/eight.txt
)
set_tests_properties(LabirintTest8 PROPERTIES PASS_REGULAR_EXPRESSION "7")

add_test(
    NAME LabirintTest9
    COMMAND Labirint ${CMAKE_CURRENT_SOURCE_DIR}/nine.txt
)
set_tests_properties(LabirintTest9 PROPERTIES PASS_REGULAR_EXPRESSION "9") # накинул 2 теста с 3 слоями