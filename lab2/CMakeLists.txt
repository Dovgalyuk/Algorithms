add_executable(Lab2 lab2.cpp)

target_include_directories(Lab2 PRIVATE
    "${CMAKE_SOURCE_DIR}/LibraryCPP"
)

target_link_libraries(Lab2 PRIVATE LibraryCPP)

enable_testing()

add_test(NAME Lab2_Example
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_example.txt)
set_property(TEST Lab2_Example PROPERTY PASS_REGULAR_EXPRESSION "BAD PUSH")

add_test(NAME Lab2_Basic
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_basic.txt)
set_property(TEST Lab2_Basic PROPERTY PASS_REGULAR_EXPRESSION "20")

add_test(NAME Lab2_BadPush
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_bad_push.txt)
set_property(TEST Lab2_BadPush PROPERTY PASS_REGULAR_EXPRESSION "BAD PUSH")

add_test(NAME Lab2_BadPop
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_bad_pop.txt)
set_property(TEST Lab2_BadPop PROPERTY PASS_REGULAR_EXPRESSION "BAD POP")

add_test(NAME Lab2_Mixed
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_mixed.txt)
set_property(TEST Lab2_Mixed PROPERTY PASS_REGULAR_EXPRESSION "BAD PUSH")

add_test(NAME Lab2_FillDrain
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_fill_drain.txt)
set_property(TEST Lab2_FillDrain PROPERTY PASS_REGULAR_EXPRESSION "STACK")

add_test(NAME Lab2_Order
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_order.txt)
set_property(TEST Lab2_Order PROPERTY PASS_REGULAR_EXPRESSION "STACK")

add_test(NAME Lab2_ZeroCapacity
    COMMAND Lab2 ${CMAKE_CURRENT_SOURCE_DIR}/test_zero_capacity.txt)
set_property(TEST Lab2_ZeroCapacity PROPERTY PASS_REGULAR_EXPRESSION "BAD PUSH")