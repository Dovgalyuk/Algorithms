add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME Lab3_Test_Canonical COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Lab3_Test_Canonical PROPERTY PASS_REGULAR_EXPRESSION "x")

add_test(NAME Lab3_Test_Left_Path COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Lab3_Test_Left_Path PROPERTY PASS_REGULAR_EXPRESSION "x")

add_test(NAME Lab3_Test_Large_Fork COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Lab3_Test_Large_Fork PROPERTY PASS_REGULAR_EXPRESSION "x")

add_test(NAME Lab3_Test_No_Path COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Lab3_Test_No_Path PROPERTY PASS_REGULAR_EXPRESSION "E")