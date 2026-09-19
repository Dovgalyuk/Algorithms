add_library(Lab1CPP STATIC Lab1CPP.cpp)
target_include_directories(Lab1CPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Lab1CPP PUBLIC LibraryCPP)

add_executable(TwoMin TwoMin.cpp)
target_link_libraries(TwoMin PRIVATE Lab1CPP)

add_executable(RLE RLE.cpp)
target_link_libraries(RLE PRIVATE Lab1CPP)


add_test(NAME TwoMin_Test1
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_1.txt)
set_property(TEST TwoMin_Test1 PROPERTY PASS_REGULAR_EXPRESSION "1 3")

add_test(NAME TwoMin_Test2
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_2.txt)
set_property(TEST TwoMin_Test2 PROPERTY PASS_REGULAR_EXPRESSION "1 2")

add_test(NAME TwoMin_Test3
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_3.txt)
set_property(TEST TwoMin_Test3 PROPERTY PASS_REGULAR_EXPRESSION "1 2")

add_test(NAME TwoMin_Test4
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_4.txt)
set_property(TEST TwoMin_Test4 PROPERTY PASS_REGULAR_EXPRESSION "1 1")

add_test(NAME TwoMin_Test5
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_5.txt)
set_property(TEST TwoMin_Test5 PROPERTY PASS_REGULAR_EXPRESSION "7 7")

add_test(NAME TwoMin_Test6
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_6.txt)
set_property(TEST TwoMin_Test6 PROPERTY PASS_REGULAR_EXPRESSION "1 10")

add_test(NAME TwoMin_Test7
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_7.txt)
set_property(TEST TwoMin_Test7 PROPERTY PASS_REGULAR_EXPRESSION "1 5")

add_test(NAME TwoMin_Test8
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_8.txt)
set_property(TEST TwoMin_Test8 PROPERTY PASS_REGULAR_EXPRESSION "-10 -7")

add_test(NAME TwoMin_Test9
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_9.txt)
set_property(TEST TwoMin_Test9 PROPERTY PASS_REGULAR_EXPRESSION "-4 -3")

add_test(NAME TwoMin_Test10
    COMMAND TwoMin ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test1_10.txt)
set_property(TEST TwoMin_Test10 PROPERTY PASS_REGULAR_EXPRESSION "3 5")


add_test(NAME RLE_Test1
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_1.txt)
set_property(TEST RLE_Test1 PROPERTY PASS_REGULAR_EXPRESSION "1 3 2 2 3 3")

add_test(NAME RLE_Test2
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_2.txt)
set_property(TEST RLE_Test2 PROPERTY PASS_REGULAR_EXPRESSION "1 2 3 4 5")

add_test(NAME RLE_Test3
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_3.txt)
set_property(TEST RLE_Test3 PROPERTY PASS_REGULAR_EXPRESSION "7")

add_test(NAME RLE_Test4
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_4.txt)
set_property(TEST RLE_Test4 PROPERTY PASS_REGULAR_EXPRESSION "9 6")

add_test(NAME RLE_Test5
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_5.txt)
set_property(TEST RLE_Test5 PROPERTY PASS_REGULAR_EXPRESSION "1 2 2 3 3")

add_test(NAME RLE_Test6
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_6.txt)
set_property(TEST RLE_Test6 PROPERTY PASS_REGULAR_EXPRESSION "1 3 2 2 3")

add_test(NAME RLE_Test7
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_7.txt)
set_property(TEST RLE_Test7 PROPERTY PASS_REGULAR_EXPRESSION "1 2 2 3 4 3 5 2")

add_test(NAME RLE_Test8
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_8.txt)
set_property(TEST RLE_Test8 PROPERTY PASS_REGULAR_EXPRESSION "-1 3 -2 2")

add_test(NAME RLE_Test9
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_9.txt)
set_property(TEST RLE_Test9 PROPERTY PASS_REGULAR_EXPRESSION "0 3 1 0 2 2")

add_test(NAME RLE_Test10
    COMMAND RLE ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test2_10.txt)
set_property(TEST RLE_Test10 PROPERTY PASS_REGULAR_EXPRESSION "1 5 7 2 2")