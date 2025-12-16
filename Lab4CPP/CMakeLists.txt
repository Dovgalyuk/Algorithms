add_executable(lab4cppclass Lab4StrtuctV1.cpp)
target_include_directories(lab4cppclass PUBLIC ../LibraryCPPTemplate)

# Test for BFS shortest path
set(EXPECTED_OUTPUT "Adjacency matrix (7 vertices):
The adjacency matrix (7 vertexes):
A\t    . 	7 	 . 	5 	 . 	 . 	 . 	
B\t    7 	 . 	 . 	 . 	7 	 . 	 . 	
C\t    . 	 . 	 . 	 . 	5 	 . 	 . 	
D\t    5 	 . 	 . 	 . 	 . 	6 	 . 	
E\t    . 	7 	5 	 . 	 . 	 . 	9 	
F\t    . 	 . 	 . 	6 	 . 	 . 	 . 	
G\t    . 	 . 	 . 	 . 	9 	 . 	 . 	
Shortest path from A to G:
Distance (edges): 3
Path: A -> B -> E -> G
")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt "${EXPECTED_OUTPUT}")

add_test(NAME TestLab4CPPClass COMMAND lab4cppclass ${CMAKE_CURRENT_SOURCE_DIR}/input.txt A G)
set_tests_properties(TestLab4CPPClass PROPERTIES TIMEOUT 10)

add_test(NAME TestLab4CPPClass_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files 
    ${CMAKE_CURRENT_BINARY_DIR}/output.txt 
    ${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt)

# Test for vector
add_executable(TestVectorCPPTemplate vector.cpp)
target_include_directories(TestVectorCPPTemplate PUBLIC ..)
add_test(TestVectorCPPTemplate TestVectorCPPTemplate)
set_tests_properties(TestVectorCPPTemplate PROPERTIES TIMEOUT 10)

# Test for graph
add_executable(TestGraphCPPTemplate graph.cpp)
target_include_directories(TestGraphCPPTemplate PUBLIC ..)
add_test(TestGraphCPPTemplate TestGraphCPPTemplate)