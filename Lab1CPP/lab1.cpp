#include <iostream>
#include <cassert>
#include "graph.h" // Assuming the Graph class is in graph.h

void testGraphIterator() {
    // Create a graph with 5 vertices
    Graph<int, int> g(5);

    // Set initial vertex marks
    for (int i = 0; i < 5; ++i) {
        g.set_vertex_mark(i, i);
    }

    // Add edges
    g.add_edge(0, 1, 10); // Edge from vertex 0 to vertex 1
    g.add_edge(1, 2, 20); // Edge from vertex 1 to vertex 2
    g.add_edge(2, 0, 30); // Edge from vertex 2 to vertex 0 (creating a cycle)
    g.add_edge(1, 3, 40); // Edge from vertex 1 to vertex 3
    g.add_edge(3, 4, 50); // Edge from vertex 3 to vertex 4
    g.add_edge(4, 1, 60); // Edge from vertex 4 to vertex 1 (creating another cycle)

    // Test iterator for vertex 1
    typename Graph<int, int>::iterator it = g.get_vertex(1)->begin();
    typename Graph<int, int>::iterator it_end = g.get_vertex(1)->end();
    int edgeCount = 0;
    // Iterate through edges connected to vertex 1
    while (it != it_end) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 4); // Vertex 1 should have 3 edges (to vertex 0, 2, and 3)

    // Test iterator for vertex 3
    it = g.get_vertex(3)->begin();
    edgeCount = 0;
    // Iterate through edges connected to vertex 3
    while (it.ptr != nullptr) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 2); // Vertex 3 should have 1 edge (to vertex 4)

    // Test iterator for vertex 4
    it = g.get_vertex(4)->begin();
    edgeCount = 0;
    // Iterate through edges connected to vertex 4
    while (it.ptr != nullptr) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 2); // Vertex 4 should have 1 edge (to vertex 1)

    // Remove an edge and test iterator again
    g.delete_edge(1); // Remove edge from vertex 1 to vertex 2
    it = g.get_vertex(1)->begin();
    edgeCount = 0;
    // Iterate through edges connected to vertex 1 after deletion
    while (it.ptr != nullptr) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 3); // Vertex 1 should now have 2 edges (to vertex 0 and 3)

    // Remove a vertex and test iterator
    g.delete_vertex(3); // Remove vertex 3
    it = g.get_vertex(1)->begin();
    edgeCount = 0;
    // Iterate through edges connected to vertex 1 after deleting vertex 3
    while (it.ptr != nullptr) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 2); // Vertex 1 should still have 2 edges (to vertex 0 and 2)

    // Test iterator for a vertex with no edges
    g.delete_edge((size_t)0); // Remove edge from vertex 0 to vertex 1
    g.delete_edge((size_t)0); // Remove edge from vertex 2 to vertex 0
    it = g.get_vertex(0)->begin();
    edgeCount = 0;
    // Iterate through edges connected to vertex 0
    while (it.ptr != nullptr) {
        edgeCount++;
        it++; // Move to the next edge
    }
    assert(edgeCount == 0); // Vertex 0 should have no edges

    std::cout << "All iterator tests passed!" << std::endl;
}

void testGraph() {
    // Create a graph with 3 vertices
    Graph<int, int> g(3);

    // Test initial vertex marks
    g.set_vertex_mark(0, 0);
    g.set_vertex_mark(1, 1);
    g.set_vertex_mark(2, 2);
    assert(g.get_vertex_mark(0) == 0);
    assert(g.get_vertex_mark(1) == 1);
    assert(g.get_vertex_mark(2) == 2);

    // Add a new vertex
    g.add_vertex(3);
    assert(g.get_vertex_mark(3) == 3);
    
    // Add edges
    g.add_edge(0, 1, 10); // Edge from vertex 0 to vertex 1
    g.add_edge(1, 2, 20); // Edge from vertex 1 to vertex 2
    g.add_edge(2, 0, 30); // Edge from vertex 2 to vertex 0

    // Test edge marks
    assert(g.get_edge_mark(0) == 10);
    assert(g.get_edge_mark(1) == 20);
    assert(g.get_edge_mark(2) == 30);

    // Test if edges exist
    assert(g.has_edge(0, 1) == true);
    assert(g.has_edge(1, 2) == true);
    assert(g.has_edge(2, 0) == true);
    assert(g.has_edge(0, 2) == false); // No direct edge from 0 to 2

    // Delete an edge
    g.delete_edge(1); // Delete edge from vertex 1 to vertex 2
    assert(g.has_edge(1, 2) == false); // Edge should no longer exist

    // Delete a vertex
    g.delete_vertex(0); // Delete vertex 0
    assert(g.has_edge(0, 1) == false); // Edge should no longer exist
    assert(g.has_edge(2, 0) == false); // Edge should no longer exist

    // Check remaining vertices
    assert(g.get_vertex(0)->get_mark() == 3); // Vertex 1 should still exist
    assert(g.get_vertex(1)->get_mark() == 1); // Vertex 2 should still exist
    assert(g.get_vertex(2)->get_mark() == 2); // Vertex 3 should still exist

    // Additional tests
    // Test deleting a vertex with edges
    g.add_edge(2, 1, 40); // Add edge from vertex 3 to vertex 1
    g.delete_vertex(1); // Delete vertex 1

    // Test getting edge and vertex marks after deletions
    assert(g.get_vertex_mark(0) == 3); // Vertex 3 should still exist
    assert(g.get_vertex_mark(1) == 2); // Vertex 2 should still exist

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testGraphIterator();
    testGraph();
    return 0;
}
