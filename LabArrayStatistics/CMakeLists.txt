add_executable(LabArrayStatistics main.cpp)

target_include_directories(LabArrayStatistics PRIVATE
    ../LibraryCPPClass
)

target_link_libraries(LabArrayStatistics PRIVATE
    LibraryCPPClass
)

add_test(
    NAME Statistics1
    COMMAND LabArrayStatistics ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_tests_properties(
    Statistics1
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Positive: 4[\r\n]+Negative: 3[\r\n]+Zero: 3"
)

add_test(
    NAME Statistics2
    COMMAND LabArrayStatistics ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)

set_tests_properties(
    Statistics2
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Positive: 5[\r\n]+Negative: 0[\r\n]+Zero: 0"
)

add_test(
    NAME Statistics3
    COMMAND LabArrayStatistics ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)

set_tests_properties(
    Statistics3
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Positive: 0[\r\n]+Negative: 5[\r\n]+Zero: 0"
)

add_test(
    NAME Statistics4
    COMMAND LabArrayStatistics ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt
)

set_tests_properties(
    Statistics4
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Positive: 0[\r\n]+Negative: 0[\r\n]+Zero: 5"
)