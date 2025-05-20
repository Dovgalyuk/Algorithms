add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

add_test(NAME TestLab2CPP COMMAND Lab2CPP input.txt)
set_tests_properties(TestLab2CPP PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})