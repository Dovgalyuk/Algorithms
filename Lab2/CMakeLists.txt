add_executable(QV2 QueueVector.cpp)

target_include_directories(QV2 PRIVATE
    ${PROJECT_SOURCE_DIR}/LibraryCPP
)

target_link_libraries(QV2 PRIVATE LibraryCPP)

add_test(
    NAME Lab2Test1
    COMMAND QV2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt
)
set_tests_properties(Lab2Test1 PROPERTIES
    PASS_REGULAR_EXPRESSION "4 8"
)

add_test(
    NAME Lab2Test2
    COMMAND QV2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt
)
set_tests_properties(Lab2Test2 PROPERTIES
    PASS_REGULAR_EXPRESSION "2 3"
)

add_test(
    NAME Lab2Test3
    COMMAND QV2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt
)
