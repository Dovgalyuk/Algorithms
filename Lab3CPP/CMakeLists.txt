add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3CPP1 PROPERTY PASS_REGULAR_EXPRESSION "9
######
#xxxX#
#x####
#xxxx#
######")

add_test(NAME TestLab3CPP2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3CPP2 PROPERTY PASS_REGULAR_EXPRESSION "11
#######
#Xxxxx#
#x###x#
#xxx#x#
#######")

add_test(NAME TestLab3CPP3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3CPP3 PROPERTY PASS_REGULAR_EXPRESSION "15
#########
#Xxxxxxx#
#x#######
#xxxxxxx#
#########")

add_test(NAME TestLab3CPP4 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST TestLab3CPP4 PROPERTY PASS_REGULAR_EXPRESSION "7
#######
#Xx#..#
#x#x#.#
#xxx#.#
#######")

add_test(NAME TestLab3CPP5 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input5.txt)
set_property(TEST TestLab3CPP5 PROPERTY PASS_REGULAR_EXPRESSION "11
######
#Xxxx#
#xxxx#
#xxx##
######")

add_test(NAME TestLab3CPP6 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input6.txt)
set_property(TEST TestLab3CPP6 PROPERTY PASS_REGULAR_EXPRESSION "18
########
#Xxxxxx#
#xxxxxx#
#xxxxxx#
########")