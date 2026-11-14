add_executable(Lab3 lab3.cpp)
target_include_directories(Lab3 PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab3 LibraryCPPClass)

add_test(NAME TestLab3_Work COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_Work PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestLab3_Corners COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_Corners PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME TestLab3_Strip COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_Strip PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestLab3_Single COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3_Single PROPERTY PASS_REGULAR_EXPRESSION "1")

add_test(NAME TestLab3_Center COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab3_Center PROPERTY PASS_REGULAR_EXPRESSION "5")
