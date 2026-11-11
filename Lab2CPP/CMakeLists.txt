cmake_minimum_required(VERSION 3.12)
project(Lab2CPP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2CPP main.cpp beule.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

enable_testing()

function(add_forth_test TEST_NAME INPUT_FILE EXPECTED_REGEX)
    add_test(
        NAME ${TEST_NAME}
        COMMAND Lab2CPP "${INPUT_FILE}"
    )
    set_tests_properties(${TEST_NAME} PROPERTIES
        PASS_REGULAR_EXPRESSION "${EXPECTED_REGEX}"
    )
endfunction()

add_forth_test(Test1_Rot "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1.in" "1[ \r\n]+3[ \r\n]+2")
add_forth_test(Test2_DupAdd "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2.in" "1[ \r\n]+2[ \r\n]+3[ \r\n]+6")
add_forth_test(Test3_SwapOver "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test3.in" "10[ \r\n]+20[ \r\n]+5[ \r\n]+7[ \r\n]+5")
add_forth_test(Test4_Math "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test4.in" "2[ \r\n]+4[ \r\n]+10")
add_forth_test(Test5_Complex "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test5.in" "41")
add_forth_test(Test6_Sub "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test6.in" "7")
add_forth_test(Test7_MulZero "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test7.in" "0")
add_forth_test(Test8_DivMod "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test8.in" "3[ \r\n]+2")
add_forth_test(Test9_Drop "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test9.in" "10")
add_forth_test(Test10_Dup "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test10.in" "15[ \r\n]+15")
add_forth_test(Test11_DivZero "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test11.in" "0")
add_forth_test(Test12_Sequence "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test12.in" "25")
add_forth_test(Test13_MultiPrint "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test13.in" "3[ \r\n]+12")
add_forth_test(Test14_SwapMulti "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test14.in" "2[ \r\n]+3[ \r\n]+1")
add_forth_test(Test15_Over "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test15.in" "4[ \r\n]+5[ \r\n]+4")
add_forth_test(Test16_SwapEdge "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test16.in" "5")
add_forth_test(Test17_OverEdge "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test17.in" "10")
add_forth_test(Test18_RotEdge "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test18.in" "2[ \r\n]+1")
add_forth_test(Test19_Negative "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test19.in" "-8[ \r\n]+-20")
add_forth_test(Test20_EmptyStack "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test20.in" "42")