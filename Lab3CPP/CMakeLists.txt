add_executable(Lab3CPP lab3.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_BINARY_DIR})

add_test(NAME TestLab3CPP COMMAND Lab3CPP) 
set_tests_properties(TestLab3CPP PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
