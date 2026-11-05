add_executable(Laba3 main.cpp)
target_include_directories(Laba3 PUBLIC ../LibraryCPP)
target_link_libraries(Laba3 LibraryCPP)

add_test(NAME TestLaba3 COMMAND Laba3 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input1.txt)
set_property(TEST TestLaba3 PROPERTY PASS_REGULAR_EXPRESSION "3 2 # 2 3 2 3")

add_test(NAME TestLaba3_2 COMMAND Laba3 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input2.txt)
set_property(TEST TestLaba3_2 PROPERTY PASS_REGULAR_EXPRESSION "9 8 5 2 1")

add_test(NAME TestLaba3_3 COMMAND Laba3 ${CMAKE_CURRENT_SOURCE_DIR}/Test/input3.txt)
set_property(TEST TestLaba3_3 PROPERTY PASS_REGULAR_EXPRESSION "3 2 # # 3 2 3")