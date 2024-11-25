add_executable(Lab6 lab6.cpp)

add_test(NAME testLab6 COMMAND Lab6 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output1.txt ${CMAKE_BINARY_DIR}/output2.txt)
