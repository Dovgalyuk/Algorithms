add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3CPP PROPERTY PASS_REGULAR_EXPRESSION "3")

add_test(NAME TestLab3CPP1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3CPP1 PROPERTY PASS_REGULAR_EXPRESSION "0")

add_test(NAME TestLab3CPP2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3CPP2 PROPERTY PASS_REGULAR_EXPRESSION "1")


