add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_test(NAME TestLab3CPP COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION "9.*######.*#xxxX#.*#x####.*#xxxx#.*######")

add_test(NAME TestLab3CPP2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION "13.*##########.*#Xxxx#####.*####x#####.*####xxx###.*######x###.*#..###xxx#.*########x#.*##########.*#....#####.*##########")

