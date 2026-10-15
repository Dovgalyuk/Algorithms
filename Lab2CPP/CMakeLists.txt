add_executable(Lab2Cpp main.cpp)
target_include_directories(Lab2Cpp PRIVATE ../LibraryCPP)
target_link_libraries(Lab2Cpp PRIVATE LibraryCPP)

add_test(
    NAME TestLab2Cpp_1
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)
set_property(
    TEST TestLab2Cpp_1
    PROPERTY PASS_REGULAR_EXPRESSION "3[\r\n]+2[\r\n]+1"
)

add_test(
    NAME TestLab2Cpp_2
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt
)
set_property(
    TEST TestLab2Cpp_2
    PROPERTY PASS_REGULAR_EXPRESSION "1[\r\n]+2[\r\n]+3[\r\n]+6"
)

add_test(
    NAME TestLab2Cpp_3
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt
)
set_property(
    TEST TestLab2Cpp_3
    PROPERTY PASS_REGULAR_EXPRESSION "6"
)

add_test(NAME TestLab2Cpp_4
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab2Cpp_4 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestLab2Cpp_5
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab2Cpp_5 PROPERTY PASS_REGULAR_EXPRESSION "-1")

add_test(NAME TestLab2Cpp_6
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST TestLab2Cpp_6 PROPERTY PASS_REGULAR_EXPRESSION "6")

add_test(NAME TestLab2Cpp_7
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input7.txt)
set_property(TEST TestLab2Cpp_7 PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME TestLab2Cpp_8
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input8.txt)
set_property(TEST TestLab2Cpp_8 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME TestLab2Cpp_9
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input9.txt)
set_property(TEST TestLab2Cpp_9 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestLab2Cpp_10
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input10.txt)
set_property(TEST TestLab2Cpp_10 PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestLab2Cpp_11
    COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input11.txt)
set_property(TEST TestLab2Cpp_11 PROPERTY PASS_REGULAR_EXPRESSION "5[\r\n]+5")