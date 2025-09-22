add_executable(Lab1C lab1.c)
target_include_directories(Lab1C PUBLIC ../LibraryC)
target_link_libraries(Lab1C LibraryC)

add_test(NAME FullTestLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input.txt)
set_property(TEST FullTestLab1C PROPERTY PASS_REGULAR_EXPRESSION "9[\ \n]+1[\ \n]*")

add_test(NAME TestTask1WithNegativeTask2Lab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input2.txt)
set_property(TEST TestTask1WithNegativeTask2Lab1C PROPERTY PASS_REGULAR_EXPRESSION "6[\\s\\n]*")

add_test(NAME TestTask2WithNegativeTask1Lab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input3.txt)
set_property(TEST TestTask2WithNegativeTask1Lab1C PROPERTY PASS_REGULAR_EXPRESSION "[\\s\\n]*3")

add_test(NAME TestZerosLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input4.txt)
set_property(TEST TestZerosLab1C PROPERTY FAIL_REGULAR_EXPRESSION "\.+")

add_test(NAME TestEmptysLab1C COMMAND Lab1C ${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input5.txt)
set_property(TEST TestEmptysLab1C PROPERTY FAIL_REGULAR_EXPRESSION "\.+")
