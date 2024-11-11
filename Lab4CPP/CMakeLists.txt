add_executable(Lab4 lab4.cpp)
#add_executable(Test test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Test4Lab4CPP COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(Test4Lab3CPP PROPERTIES PASS_REGULAR_EXPRESSION "4")