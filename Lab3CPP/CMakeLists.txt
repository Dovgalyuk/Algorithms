add_executable(Lab3CPP task.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME Lab3_Test1
         COMMAND Lab3CPP
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.txt
         ${CMAKE_CURRENT_BINARY_DIR}/out1.txt)
add_test(NAME Lab3_Test1_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
         ${CMAKE_CURRENT_BINARY_DIR}/out1.txt
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1_expected.txt)
set_tests_properties(Lab3_Test1_check PROPERTIES DEPENDS Lab3_Test1)

add_test(NAME Lab3_Test2
         COMMAND Lab3CPP
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2.txt
         ${CMAKE_CURRENT_BINARY_DIR}/out2.txt)
add_test(NAME Lab3_Test2_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
         ${CMAKE_CURRENT_BINARY_DIR}/out2.txt
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2_expected.txt)
set_tests_properties(Lab3_Test2_check PROPERTIES DEPENDS Lab3_Test2)

add_test(NAME Lab3_Test3
         COMMAND Lab3CPP
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3.txt
         ${CMAKE_CURRENT_BINARY_DIR}/out3.txt)
add_test(NAME Lab3_Test3_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
         ${CMAKE_CURRENT_BINARY_DIR}/out3.txt
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3_expected.txt)
set_tests_properties(Lab3_Test3_check PROPERTIES DEPENDS Lab3_Test3)

add_test(NAME Lab3_Test4
         COMMAND Lab3CPP
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4.txt
         ${CMAKE_CURRENT_BINARY_DIR}/out4.txt)
add_test(NAME Lab3_Test4_check
         COMMAND ${CMAKE_COMMAND} -E compare_files
         ${CMAKE_CURRENT_BINARY_DIR}/out4.txt
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test4_expected.txt)
set_tests_properties(Lab3_Test4_check PROPERTIES DEPENDS Lab3_Test4)

add_test(NAME Lab3_Test5
         COMMAND Lab3CPP
         ${CMAKE_CURRENT_SOURCE_DIR}/tests/test5.txt
         ${CMAKE_CURRENT_BINARY_DIR}/out5.txt)
set_tests_properties(Lab3_Test5 PROPERTIES WILL_FAIL TRUE)