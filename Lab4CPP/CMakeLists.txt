add_executable(Lab4 lab4.cpp)
#add_executable(Test test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

#add_test(NAME TestLab4 COMMAND Lab4 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)
#add_test(NAME TestLab4_EqualFiles COMMAND Test ${CMAKE_BINARY_DIR}/output.txt ${CMAKE_CURRENT_SOURCE_DIR}/correct_output.txt)