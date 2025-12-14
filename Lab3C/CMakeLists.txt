add_executable(Lab3C lab3.c game.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)

# Test 1: Already solved
add_test(NAME TestLab3C_01_AlreadySolved
         COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_01_already_solved.txt | ./Lab3C")
set_property(TEST TestLab3C_01_AlreadySolved PROPERTY PASS_REGULAR_EXPRESSION "123456780")

# Test 2: One move from goal
add_test(NAME TestLab3C_02_OneMove
         COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_02_one_move.txt | ./Lab3C")
set_property(TEST TestLab3C_02_OneMove PROPERTY PASS_REGULAR_EXPRESSION "123456708.*123456780")

# Test 3: Two moves from goal
add_test(NAME TestLab3C_03_TwoMoves
         COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_03_two_moves.txt | ./Lab3C")
set_property(TEST TestLab3C_03_TwoMoves PROPERTY PASS_REGULAR_EXPRESSION "123450786.*123456780")

# Test 4: Simple puzzle
add_test(NAME TestLab3C_04_Sample
         COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_04_sample.txt | ./Lab3C")
set_property(TEST TestLab3C_04_Sample PROPERTY PASS_REGULAR_EXPRESSION "312456780.*123456780")

# Test 5: Harder puzzle
add_test(NAME TestLab3C_05_Harder
         COMMAND bash -c "cat ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_05_harder.txt | ./Lab3C")
set_property(TEST TestLab3C_05_Harder PROPERTY PASS_REGULAR_EXPRESSION "821043765.*123456780")
