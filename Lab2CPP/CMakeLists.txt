add_executable(Lab2CPP src/assembler.cpp src/operations.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_test(NAME TestLab2_1
    COMMAND sh -c "\"$<TARGET_FILE:Lab2CPP>\" \"${TESTS_DIR}/test1.txt\" | diff -u \"${TESTS_DIR}/test1_expected.txt\" -")

add_test(NAME TestLab2_2
    COMMAND sh -c "\"$<TARGET_FILE:Lab2CPP>\" \"${TESTS_DIR}/test2.txt\" | diff -u \"${TESTS_DIR}/test2_expected.txt\" -")

add_test(NAME TestLab2_3
    COMMAND sh -c "\"$<TARGET_FILE:Lab2CPP>\" \"${TESTS_DIR}/test3.txt\" | diff -u \"${TESTS_DIR}/test3_expected.txt\" -")

add_test(NAME TestLab2_4
    COMMAND sh -c "\"$<TARGET_FILE:Lab2CPP>\" \"${TESTS_DIR}/test4.txt\" | diff -u \"${TESTS_DIR}/test4_expected.txt\" -")
