add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME FlowSimple COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/simple.txt)
set_tests_properties(FlowSimple PROPERTIES
    PASS_REGULAR_EXPRESSION "^5\n$" TIMEOUT 10)

add_test(NAME FlowNoPath COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/no_path.txt)
set_tests_properties(FlowNoPath PROPERTIES
    PASS_REGULAR_EXPRESSION "^0\n$" TIMEOUT 10)

add_test(NAME FlowBottleneck COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/bottleneck.txt)
set_tests_properties(FlowBottleneck PROPERTIES
    PASS_REGULAR_EXPRESSION "^3\n$" TIMEOUT 10)

add_test(NAME FlowReverse COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/reverse.txt)
set_tests_properties(FlowReverse PROPERTIES
    PASS_REGULAR_EXPRESSION "^2\n$" TIMEOUT 10)

add_test(NAME FlowOpposite COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/opposite.txt)
set_tests_properties(FlowOpposite PROPERTIES
    PASS_REGULAR_EXPRESSION "^5\n$" TIMEOUT 10)

add_test(NAME FlowZero COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/zero.txt)
set_tests_properties(FlowZero PROPERTIES
    PASS_REGULAR_EXPRESSION "^0\n$" TIMEOUT 10)

add_test(NAME FlowNegative COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/negative.txt)
set_tests_properties(FlowNegative PROPERTIES WILL_FAIL TRUE TIMEOUT 10)

add_test(NAME FlowUnknown COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/unknown.txt)
set_tests_properties(FlowUnknown PROPERTIES WILL_FAIL TRUE TIMEOUT 10)

add_test(NAME FlowBroken COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/broken.txt)
set_tests_properties(FlowBroken PROPERTIES WILL_FAIL TRUE TIMEOUT 10)

add_test(NAME FlowSame COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/same.txt)
set_tests_properties(FlowSame PROPERTIES WILL_FAIL TRUE TIMEOUT 10)

add_test(NAME FlowMissingTerminal COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/tests/missing_terminal.txt)
set_tests_properties(FlowMissingTerminal PROPERTIES WILL_FAIL TRUE TIMEOUT 10)

add_test(NAME FlowNoArgument COMMAND Lab4CPP)
set_tests_properties(FlowNoArgument PROPERTIES WILL_FAIL TRUE TIMEOUT 10)