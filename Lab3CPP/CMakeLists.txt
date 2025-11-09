add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)
set_property(TEST TestLab3CPP PROPERTY PASS_REGULAR_EXPRESSION "Start City1 City2 End\r?\n")

add_test(NAME TestLab3CPP_1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_SOURCE_DIR}/output1.txt)
set_property(TEST TestLab3CPP_1 PROPERTY PASS_REGULAR_EXPRESSION "Not found\r?\n")

add_test(NAME TestLab3CPP_4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_SOURCE_DIR}/output2.txt)
set_property(TEST TestLab3CPP_4 PROPERTY PASS_REGULAR_EXPRESSION "Start D E End\r?\n")