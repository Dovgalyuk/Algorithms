add_executable(Lab4CPP main.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP_1
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out1.txt)
add_test(NAME TestLab4CPP_1_check
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt)
set_property(TEST TestLab4CPP_1_check PROPERTY PASS_REGULAR_EXPRESSION "Total Cost: 3   Steps: 3")

add_test(NAME TestLab4CPP_2
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out2.txt)
add_test(NAME TestLab4CPP_2_check
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt)
set_property(TEST TestLab4CPP_2_check PROPERTY PASS_REGULAR_EXPRESSION "Total Cost: 7   Steps: 5")

add_test(NAME TestLab4CPP_3
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out3.txt)
add_test(NAME TestLab4CPP_3_check
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt)
set_property(TEST TestLab4CPP_3_check PROPERTY PASS_REGULAR_EXPRESSION "Total Cost: 5   Steps: 5")

add_test(NAME TestLab4CPP_4
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out4.txt)
add_test(NAME TestLab4CPP_4_check
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt)
set_property(TEST TestLab4CPP_4_check PROPERTY PASS_REGULAR_EXPRESSION "Total Cost: 5   Steps: 5")

add_test(NAME TestLab4CPP_5
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out5.txt)
add_test(NAME TestLab4CPP_5_check
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt)
set_property(TEST TestLab4CPP_5_check PROPERTY PASS_REGULAR_EXPRESSION "Total Cost: 7   Steps: 7")