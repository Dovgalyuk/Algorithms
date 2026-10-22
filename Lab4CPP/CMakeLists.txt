add_executable(KruskalMST kruskal_mst.cpp)
target_include_directories(KruskalMST PUBLIC ../LibraryCPPTemplate)

add_test(NAME Kruskal_Tree
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_tree.txt)
set_tests_properties(Kruskal_Tree PROPERTIES
    PASS_REGULAR_EXPRESSION "Minimum spanning tree weight: 12")

add_test(NAME Kruskal_Split
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_split.txt)
set_tests_properties(Kruskal_Split PROPERTIES
    PASS_REGULAR_EXPRESSION "No spanning tree")

add_test(NAME Kruskal_One
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_one.txt)
set_tests_properties(Kruskal_One PROPERTIES
    PASS_REGULAR_EXPRESSION "Minimum spanning tree weight: 0")

add_test(NAME Kruskal_Triangle
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_triangle.txt)
set_tests_properties(Kruskal_Triangle PROPERTIES
    PASS_REGULAR_EXPRESSION "Minimum spanning tree weight: 2")

add_test(NAME Kruskal_Empty
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_empty.txt)
set_tests_properties(Kruskal_Empty PROPERTIES
    PASS_REGULAR_EXPRESSION "Minimum spanning tree weight: 0")

add_test(NAME Kruskal_Bidir
    COMMAND KruskalMST ${CMAKE_CURRENT_SOURCE_DIR}/sample_bidir.txt)
set_tests_properties(Kruskal_Bidir PROPERTIES
    PASS_REGULAR_EXPRESSION "Minimum spanning tree weight: 7")
