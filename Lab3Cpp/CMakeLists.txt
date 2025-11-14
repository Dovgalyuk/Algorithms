add_executable(Lab3Cpp lab3.cpp)
target_include_directories(Lab3Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab3Cpp LibraryCPP)

add_test(NAME TestLab3Cpp COMMAND Lab3Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3Cpp PROPERTY PASS_REGULAR_EXPRESSION "B\nC\n")