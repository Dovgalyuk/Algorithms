add_executable(Lab1CPP main.cpp)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)

add_test(NAME TestLab1CPP COMMAND $<TARGET_FILE:Lab1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_tests_properties(TestLab1CPP PROPERTIES PASS_REGULAR_EXPRESSION "Two smallest elements: 2, 4[\r\n]+Unique elements: 2 7 5")

add_test(NAME TestLab1CPPNoUn COMMAND $<TARGET_FILE:Lab1CPP> ${CMAKE_CURRENT_SOURCE_DIR}/inputunun.txt)
set_tests_properties(TestLab1CPPNoUn PROPERTIES PASS_REGULAR_EXPRESSION "Two smallest elements: 1, 1[\r\n]+Unique elements: none")