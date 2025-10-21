add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND $<TARGET_FILE:Lab2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab2CPP PROPERTY PASS_REGULAR_EXPRESSION  "72 101 108")

add_test(NAME TestLab2CPP2 COMMAND $<TARGET_FILE:Lab2CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt ${CMAKE_CURRENT_SOURCE_DIR}/input_commands2.txt)
set_property(TEST TestLab2CPP2 PROPERTY PASS_REGULAR_EXPRESSION  "10 9 8")


