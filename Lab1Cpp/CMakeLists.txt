add_executable(Lab1Cpp lab1.cpp)
target_include_directories(Lab1Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab1Cpp LibraryCPP)

add_test(NAME TestLab1Cpp COMMAND Lab1Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab1Cpp PROPERTY PASS_REGULAR_EXPRESSION "5\\.00.*-3\\.67.*10 5 -1 2 7")