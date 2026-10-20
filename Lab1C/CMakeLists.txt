add_executable(Lab1C lab1.cpp)

target_include_directories(Lab1C PRIVATE
    ${CMAKE_SOURCE_DIR}/LibraryCPP
)
target_link_libraries(Lab1C PRIVATE LibraryCPP)


add_test(NAME TestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab1C PROPERTY PASS_REGULAR_EXPRESSION "YES")


add_test(NAME TestExtra COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestExtra PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestNested COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestNested PROPERTY PASS_REGULAR_EXPRESSION "YES")

add_test(NAME TestExtraClosing COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestExtraClosing PROPERTY PASS_REGULAR_EXPRESSION "NO")

add_test(NAME TestUnclosedQuote COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestUnclosedQuote PROPERTY PASS_REGULAR_EXPRESSION "NO")