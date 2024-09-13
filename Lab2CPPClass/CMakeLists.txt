add_executable(Lab2CPPClass lab2.cpp)
add_executable(Test test.cpp)
target_include_directories(Lab2CPPClass PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab2CPPClass LibraryCPPClass)

add_test(NAME TestLab2CPPClass COMMAND Lab2CPPClass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)
add_test(NAME TestLab2CPPClass_EqualFiles COMMAND Test ${CMAKE_BINARY_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/best_output.txt)
