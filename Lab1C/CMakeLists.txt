add_executable(Lab1C lab1.cpp)
target_include_directories(Lab1C PUBLIC ../LibraryCPP)
target_link_libraries(Lab1C LibraryCPP)

add_test(NAME Test1 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Test1 PROPERTY PASS_REGULAR_EXPRESSION "5\\.454545.*\\(1,2\\) \\(2,1\\) \\(3,1\\)")

add_test(NAME Test2 COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Test2 PROPERTY PASS_REGULAR_EXPRESSION "3\\.333333.*\\(7,5\\)")