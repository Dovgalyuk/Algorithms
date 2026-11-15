add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Test1Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output1.txt)
set_property(TEST Test1Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "2.*1 2 5.*3 4")

add_test(NAME Test2Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output2.txt)
set_property(TEST Test2Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "1.*1 ")

add_test(NAME Test3Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output3.txt)
set_property(TEST Test3Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "4.*1 .*2 .*3 .*4 ")

add_test(NAME Test4Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input4.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output4.txt)
set_property(TEST Test4Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "1.*1 2 3 4 5 6 7")

add_test(NAME Test5Lab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/Tests/input5.txt ${CMAKE_CURRENT_SOURCE_DIR}/Tests/output5.txt)
set_property(TEST Test5Lab3CPP PROPERTY PASS_REGULAR_EXPRESSION "3.*1 4.*2 5.*3 6")
