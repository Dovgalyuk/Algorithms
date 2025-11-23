add_executable(Lab4Cpp lab4.cpp)
target_include_directories(Lab4Cpp PUBLIC ../LibraryCPP)
target_include_directories(Lab4Cpp PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab4Cpp LibraryCPP)

add_test(NAME TestLab4Cpp COMMAND Lab4Cpp ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4Cpp PROPERTY PASS_REGULAR_EXPRESSION "4\nA B C D")