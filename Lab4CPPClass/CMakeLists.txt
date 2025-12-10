add_executable(lab4cppclass Lab4StrtuctV1.cpp)
target_include_directories(lab4cppclass PUBLIC ../LibraryCPPTemplate)
# target_link_libraries(lab4cppclass LibraryCPPTemplate)
set(EXPECTED_OUTPUT "7
A
B
C
D
E
F
G
0 7 0 5 0 0 0 
7 0 0 0 7 0 0 
0 0 0 0 5 0 0 
5 0 0 0 0 6 0 
0 7 5 0 0 0 9 
0 0 0 6 0 0 0 
0 0 0 0 9 0 0 
")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt "${EXPECTED_OUTPUT}")

add_test(NAME TestLab4CPPClass COMMAND lab4cppclass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_SOURCE_DIR}/output.txt)
add_test(NAME TestLab4CPPClass_Compare
COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/output.txt ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt)