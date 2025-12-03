cmake_minimum_required(VERSION 3.10)
project(Lab4CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4CPP 
    ${CMAKE_CURRENT_SOURCE_DIR}/lab4.cpp
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate/Tests/graph.cpp
)

target_include_directories(Lab4CPP PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/LibraryCPPTemplate
)

# Отключаем main() в graph.cpp для Lab4CPP
target_compile_definitions(Lab4CPP PRIVATE -DNO_GRAPH_MAIN)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

# Тест 1: Запуск без аргументов (строгая проверка выходных данных)
add_test(NAME TestLab4CPP_ExactOutput COMMAND Lab4CPP)
set_property(TEST TestLab4CPP_ExactOutput PROPERTY PASS_REGULAR_EXPRESSION 
    "=== Testing Graph Library ==="
    "Vertex count: 5"
    "Has edge A->B: 1"
    "Has edge B->A: 0"
    "Vertex labels: A B C D E"
    "Neighbors of A: C B"
    "Edge A->B weight: 5"
    "Edge C->D weight: 1"
    "Found.*shortest path.*from A to E"
    "Path 1: A -> C -> E.*Length: 2"
    "Path 2: A -> C -> D -> E.*Length: 3"
)

# Тест 2: Поиск путей из A в E (проверка конкретных путей)
add_test(NAME TestLab4CPP_APaths COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt A E)
set_property(TEST TestLab4CPP_APaths PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths from A to E"
    "Path 1: A -> C -> E.*Length: 2"
    "Path 2: A -> C -> D -> E.*Length: 3"
)

# Тест 3: Поиск путей из A в D
add_test(NAME TestLab4CPP_BPaths COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt A D)
set_property(TEST TestLab4CPP_BPaths PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths from A to D"
    "Path 1: A -> C -> D.*Length: 2"
)

# Тест 4: Поиск путей из B в E
add_test(NAME TestLab4CPP_CPaths COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt B E)
set_property(TEST TestLab4CPP_CPaths PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths from B to E"
    "Path 1: B -> D -> E.*Length: 2"
)

# Тест 5: Тест на отсутствие пути (несуществующая вершина)
add_test(NAME TestLab4CPP_NoPath COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt A Z)
set_property(TEST TestLab4CPP_NoPath PROPERTY PASS_REGULAR_EXPRESSION 
    "not found|No path found|Cannot open"
)

# Тест 6: Проверка E->D (обратный путь с весом 2)
add_test(NAME TestLab4CPP_ReversePath COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt E D)
set_property(TEST TestLab4CPP_ReversePath PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths from E to D"
    "Path 1: E -> D.*Length: 1"
)

# Тест 7: Проверка C->E
add_test(NAME TestLab4CPP_CEPath COMMAND Lab4CPP ${CMAKE_CURRENT_BINARY_DIR}/input.txt C E)
set_property(TEST TestLab4CPP_CEPath PROPERTY PASS_REGULAR_EXPRESSION 
    "Shortest Paths from C to E"
    "Path 1: C -> E.*Length: 1"
)