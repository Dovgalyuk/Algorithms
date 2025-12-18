add_executable(Lab3C lab3.c)
target_include_directories(Lab3C PUBLIC ../LibraryC)
target_link_libraries(Lab3C LibraryC)

add_test(NAME WorkTest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST WorkTest PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME SimplePerformanceTest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST SimplePerformanceTest PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TwoWaysTest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TwoWaysTest PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME LackOfPathsTest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST LackOfPathsTest PROPERTY PASS_REGULAR_EXPRESSION "0, There are no paths.")

add_test(NAME LackOfETest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST LackOfETest PROPERTY PASS_REGULAR_EXPRESSION "0, There are no paths.")

add_test(NAME StandartInputTest COMMAND Lab3C ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST StandartInputTest PROPERTY PASS_REGULAR_EXPRESSION "3")