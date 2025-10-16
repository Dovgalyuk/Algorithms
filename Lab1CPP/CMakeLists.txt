add_executable(Lab1CPP lab1.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND $<TARGET_FILE:Lab1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1CPP PROPERTIES PASS_REGULAR_EXPRESSION "5,0 ")

add_test(NAME TestLab1CPPNoUn COMMAND $<TARGET_FILE:Lab1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/inputunun.txt)
set_tests_properties(TestLab1CPPNoUn PROPERTIES PASS_REGULAR_EXPRESSION "1 2 3 4 ")
