#include <iostream>
#include <cassert>
#include "graph.h" 

void testGraphIterator() {
    Graph<int, int> g(5);

    for (int i = 0; i < 5; ++i) 
        g.set_vertex_mark(i, i);

    // Add edges
    g.add_edge(0, 1, 10); 
    g.add_edge(1, 2, 20); 
    g.add_edge(2, 0, 30); // Edge from vertex 2 to vertex 0 (creating a cycle)
    g.add_edge(1, 3, 40); 
    g.add_edge(3, 4, 50); 
    g.add_edge(4, 1, 60); // Edge from vertex 4 to vertex 1 (creating another cycle)

    typename Graph<int, int>::iterator it = g.begin(1);
    typename Graph<int, int>::iterator it_end = g.end(1);
    int edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++; 
    }
    assert(edgeCount == 4);

    it = g.begin(3);
    it_end = g.end(3);
    edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++;
    }
    assert(edgeCount == 2);

    it = g.begin(4);
    it_end = g.end(4);
    edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++;
    }
    assert(edgeCount == 2);

    g.delete_edge(1);
    it = g.begin(1);
    it_end = g.end(1);
    edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++;
    }
    assert(edgeCount == 3); 

    g.delete_vertex(3); 
    it = g.begin(1);
    it_end = g.end(1);
    edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++;
    }
    assert(edgeCount == 2);

    g.delete_edge((size_t)0); 
    g.delete_edge((size_t)2);
    it = g.begin(0);
    it_end = g.end(0);
    edgeCount = 0;
    while (it != it_end) {
        edgeCount++;
        it++;
    }
    assert(edgeCount == 0);

    assert(g.has_edge(1, 3) == false);
    assert(g.has_edge(3, 1) == true);

    std::cout << "All iterator tests passed!" << std::endl;
}

void testGraph() {
    Graph<int, int> g(3);

    g.set_vertex_mark(0, 0);
    g.set_vertex_mark(1, 1);
    g.set_vertex_mark(2, 2);
    assert(g.get_vertex_mark(0) == 0);
    assert(g.get_vertex_mark(1) == 1);
    assert(g.get_vertex_mark(2) == 2);

    g.add_vertex(3);
    assert(g.get_vertex_mark(3) == 3);
    
    g.add_edge(0, 1, 10); 
    g.add_edge(1, 2, 20); 
    g.add_edge(2, 0, 30);

    assert(g.get_edge_mark(0) == 10);
    assert(g.get_edge_mark(1) == 20);
    assert(g.get_edge_mark(2) == 30);

    assert(g.has_edge(0, 1) == true);
    assert(g.has_edge(1, 2) == true);
    assert(g.has_edge(2, 0) == true);
    assert(g.has_edge(0, 2) == false);

    g.delete_edge(1);
    assert(g.has_edge(1, 2) == false); 

    g.delete_vertex(0); 
    assert(g.has_edge(0, 1) == false); 
    assert(g.has_edge(2, 0) == false);

    assert(g.get_vertex(0)->get_mark() == 3); 
    assert(g.get_vertex(1)->get_mark() == 1); 
    assert(g.get_vertex(2)->get_mark() == 2);

    g.add_edge(2, 1, 40);
    g.delete_vertex(1);

    assert(g.get_vertex_mark(0) == 3);
    assert(g.get_vertex_mark(1) == 2);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testGraphIterator();
    testGraph();
    return 0;
}
