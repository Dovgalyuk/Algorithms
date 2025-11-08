add_executable(Lab2Cpp lab2.cpp)
target_include_directories(Lab2Cpp PUBLIC ../LibraryCPP)
target_link_libraries(Lab2Cpp LibraryCPP)

add_test(NAME TestLab2Cpp COMMAND Lab2Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2Cpp PROPERTY PASS_REGULAR_EXPRESSION "27")