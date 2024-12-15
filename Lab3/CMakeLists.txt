add_executable(Lab3 lab3.cpp)
include_directories(${CMAKE_SOURCE_DIR}/LibraryCPPTemplate)

add_test(NAME Lab3Test COMMAND Lab3 ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/output.txt)
