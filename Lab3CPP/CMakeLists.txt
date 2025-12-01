add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

enable_testing()
add_test(NAME TestLab3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

add_test(NAME TestLab3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3 PROPERTY PASS_REGULAR_EXPRESSION "4")

add_test(NAME TestLab3_1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_1 PROPERTY PASS_REGULAR_EXPRESSION "2")

add_test(NAME TestLab3_2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_2 PROPERTY PASS_REGULAR_EXPRESSION "5")

add_test(NAME TestLab3_3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_3 PROPERTY PASS_REGULAR_EXPRESSION "-1")