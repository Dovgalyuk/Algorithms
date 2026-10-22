add_executable(Lab4CPP main.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP_1
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out1.txt)
add_test(NAME TestLab4CPP_1_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out1.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_expected.txt)

add_test(NAME TestLab4CPP_2
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out2.txt)
add_test(NAME TestLab4CPP_2_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out2.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_expected.txt)

add_test(NAME TestLab4CPP_3
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out3.txt)
add_test(NAME TestLab4CPP_3_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out3.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3_expected.txt)

add_test(NAME TestLab4CPP_4
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out4.txt)
add_test(NAME TestLab4CPP_4_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out4.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4_expected.txt)

add_test(NAME TestLab4CPP_5
         COMMAND Lab4CPP
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt
                 ${CMAKE_CURRENT_BINARY_DIR}/out5.txt)
add_test(NAME TestLab4CPP_5_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
                 ${CMAKE_CURRENT_BINARY_DIR}/out5.txt
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5_expected.txt)