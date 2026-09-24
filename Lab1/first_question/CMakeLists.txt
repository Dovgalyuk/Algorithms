add_executable(Task1 two_small_elem.cpp)

target_include_directories(Task1 PUBLIC ../../LibraryCPP)
target_link_libraries(Task1 LibraryCPP)

add_test(NAME Test1Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_1.txt)
set_property(TEST Test1Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "1 3")

add_test(NAME Test2Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_2.txt)
set_property(TEST Test2Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "2 2")

add_test(NAME Test3Task1 COMMAND Task1 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_3.txt)
set_property(TEST Test3Task1 PROPERTY PASS_REGULAR_EXPRESSION
    "-20 -20")