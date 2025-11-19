#add_executable(Lab1CPP main.cpp)
#target_include_directories(Lab1CPP PUBLIC ../LibraryCPPClass)
#target_link_libraries(Lab1CPP LibraryCPPClass)

#add_test(NAME TestLab1C COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
#set_tests_properties(TestLab1C PROPERTIES PASS_REGULAR_EXPRESSION "6.5.*1 2 3")
#add_test(NAME TestLab2C COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
#set_tests_properties(TestLab2C PROPERTIES PASS_REGULAR_EXPRESSION "3.*2 3 4")