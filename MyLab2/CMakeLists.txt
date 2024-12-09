add_executable(MyLab2 lab2.cpp)

include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME MyLab2Test COMMAND MyLab2 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)