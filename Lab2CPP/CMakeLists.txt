add_executable(Lab2CPP lab2.cpp)
target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab2CPP LibraryCPP)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_BINARY_DIR})

add_test(NAME TestLab2CPP COMMAND Lab2CPP) 
set_tests_properties(TestLab2CPP PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
