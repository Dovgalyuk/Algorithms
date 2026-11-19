add_executable(Lab1C
    lab1.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPP/queue.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPP/vector.cpp
)

target_include_directories(Lab1C PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)
target_link_libraries(Lab1C PRIVATE LibraryCPP)

enable_testing()

add_test(NAME TestSimple COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt output1.txt)
set_property(TEST TestSimple PROPERTY PASS_REGULAR_EXPRESSION "0 1 1 2 2")

add_test(NAME TestDisconnected COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt output2.txt)
set_property(TEST TestDisconnected PROPERTY PASS_REGULAR_EXPRESSION "0 1 -1 -1")

add_test(NAME TestSingleVertex COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt output3.txt)
set_property(TEST TestSingleVertex PROPERTY PASS_REGULAR_EXPRESSION "^0")

add_test(NAME TestChain COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt output4.txt)
set_property(TEST TestChain PROPERTY PASS_REGULAR_EXPRESSION "0 1 2 3 4 5")

add_test(NAME TestCycle COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt output5.txt)
set_property(TEST TestCycle PROPERTY PASS_REGULAR_EXPRESSION "0 1 1 2")

