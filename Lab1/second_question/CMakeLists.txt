add_executable(Task2 most_freq_elem.cpp)

target_include_directories(Task2 PUBLIC ../../LibraryCPP)
target_link_libraries(Task2 LibraryCPP)

add_test(NAME Test1Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_1.txt)
set_property(TEST Test1Task2 PROPERTY PASS_REGULAR_EXPRESSION
    "5")

add_test(NAME Test2Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_2.txt)
set_property(TEST Test2Task2 PROPERTY PASS_REGULAR_EXPRESSION
    "1000")

add_test(NAME Test3Task2 COMMAND Task2 ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_3.txt)
set_property(TEST Test3Task2 PROPERTY PASS_REGULAR_EXPRESSION
    "1")