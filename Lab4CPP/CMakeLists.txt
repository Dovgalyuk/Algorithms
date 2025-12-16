[file name]: Lab4CPP/CMakeLists.txt
[file content begin]
# Проект для поиска кратчайших путей в графе
project(Lab4CPP)

# Исполняемый файл для BFS
add_executable(Lab4CPP Lab4StrtuctV1.cpp)
target_link_libraries(Lab4CPP LibraryCPPTemplate)

# Тест для BFS shortest path
set(EXPECTED_OUTPUT "Graph loaded successfully from \${CMAKE_CURRENT_SOURCE_DIR}/input.txt
Number of vertices: 7

Adjacency matrix (7 vertices):
\tA\tB\tC\tD\tE\tF\tG\t
A\t.\t7\t.\t5\t.\t.\t.\t
B\t7\t.\t.\t.\t7\t.\t.\t
C\t.\t.\t.\t.\t5\t.\t.\t
D\t5\t.\t.\t.\t.\t6\t.\t
E\t.\t7\t5\t.\t.\t.\t9\t
F\t.\t.\t.\t6\t.\t.\t.\t
G\t.\t.\t.\t.\t9\t.\t.\t

Searching shortest path from 'A' to 'G'...
Shortest path found!
Distance (number of edges): 3
Path: A -> B -> E -> G
")

file(WRITE \${CMAKE_CURRENT_BINARY_DIR}/expected_output.txt "\${EXPECTED_OUTPUT}")

add_test(NAME TestLab4CPP
    COMMAND Lab4CPP \${CMAKE_CURRENT_SOURCE_DIR}/input.txt A G)
set_tests_properties(TestLab4CPP PROPERTIES TIMEOUT 10)
[file content end]